#include <iostream>
#include <dbus/dbus.h>

static bool check_error(DBusError* error)
{
    if (dbus_error_is_set(error)) {
        std::cerr << error->name << ", " << error->message << std::endl;
        dbus_error_free(error);
        return false;
    }
    return true;
}

int main()
{
    DBusError error;
    dbus_error_init(&error);

    DBusConnection* connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    if (!check_error(&error) || !connection) {
        std::cerr << "connection error\n";
        return -3;
    }

    const char* bus_name = "org.freedesktop.timedate1";
    const char* object_path = "/org/freedesktop/timedate1";
    const char* interface = "org.freedesktop.DBus.Properties";
    const char* method = "Get";

    const char* arg1 = "org.freedesktop.timedate1";
    const char* arg2 = "Timezone";

    DBusMessage* send_message = dbus_message_new_method_call(bus_name,
                                                             object_path,
                                                             interface, 
                                                             method);

    if(!send_message) {
        std::cerr << "dbus_message_new_method_call return NULL\n";
        return -1;
    }

    DBusMessageIter iter;
    dbus_message_iter_init_append(send_message, &iter);

    if(!dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &arg1)) {
        std::cerr << "Error: Failed append parameter: " << arg1 << std::endl;
        return -2;
    }

    if(!dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &arg2)) {
        std::cerr << "Error: Failed append parameter: " << arg2 << std::endl;
        return -2;
    }

    const static int SEND_TIMEOUT = 1000;
    DBusMessage* reply_message = dbus_connection_send_with_reply_and_block(connection,
                                                                           send_message,
                                                                           SEND_TIMEOUT,
                                                                           &error);

    dbus_message_unref(send_message);

    if (!check_error(&error)) {
        return -4;
    }

    DBusMessageIter iter_c;
    dbus_message_iter_init(reply_message, &iter_c);
    int dbus_type = dbus_message_iter_get_arg_type(&iter_c);

    const char* reply = "";

    switch(dbus_type) {
        case DBUS_TYPE_STRING:
            // If basic dbus type
            dbus_message_iter_get_basic(&iter_c, &reply);
        break;

        case DBUS_TYPE_VARIANT: {
            char* signature = dbus_message_iter_get_signature(&iter_c);

            if (std::string(signature) == "v") {
                DBusMessageIter iter_v;
                // If variant container dbus type
                dbus_message_iter_recurse(&iter_c, &iter_v);

                if (dbus_message_iter_get_arg_type(&iter_v) != DBUS_TYPE_STRING) {
                    std::cerr << "Error: Unexpected type\n";
                    return -9;
                }

                dbus_message_iter_get_basic(&iter_v, &reply);
            }
        }
        break;

        default:
            std::cerr << "Error: Unexpected dbus type argument: "
                      << dbus_type << std::endl;
            return -6;
    }

    std::cout << arg2 << ": " << reply << std::endl;

    dbus_message_unref(reply_message);

    return 0;
}
