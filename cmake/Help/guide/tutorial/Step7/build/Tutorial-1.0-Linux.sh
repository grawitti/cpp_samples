#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --version         print cmake installer version
  --prefix=dir      directory in which to install
  --include-subdir  include the Tutorial-1.0-Linux subdirectory
  --exclude-subdir  exclude the Tutorial-1.0-Linux subdirectory
  --skip-license    accept license
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "Tutorial Installer Version: 1.0, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
This is the open source License.txt file introduced in
CMake/Tutorial/Step7...

____cpack__here_doc____
    echo
    while true
      do
        echo "Do you accept the license? [yn]: "
        read line leftover
        case ${line} in
          y* | Y*)
            cpack_license_accepted=TRUE
            break;;
          n* | N* | q* | Q* | e* | E*)
            echo "License not accepted. Exiting ..."
            exit 1;;
        esac
      done
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the Tutorial will be installed in:"
    echo "  \"${toplevel}/Tutorial-1.0-Linux\""
    echo "Do you want to include the subdirectory Tutorial-1.0-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/Tutorial-1.0-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

extractor="pax -r"
command -v pax > /dev/null 2> /dev/null || extractor="tar xf -"

tail $use_new_tail_syntax +152 "$0" | gunzip | (cd "${toplevel}" && ${extractor}) || cpack_echo_exit "Problem unpacking the Tutorial-1.0-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;
� �I^ �\t[ř��į�81�$4OE�m���r��N�4<�E�d[�,�*8YR�h�1�p�M)�d���K{��ݥa϶��&��I�.d��n�a� .���v��3WsG�&B�m5>������}���u�D��s:��jj$L]�j�<՝���n���z��t�k��H�������V%���}k����|������ǿV��ה���P4w�No�<<�Ֆ�����N��׿��v!�yz�0w���e���o팕��93�������8Gcǿ��o�����p)�z���7�����:�+O;4�����~����n����Zd3��،�s�_�JQ��|U:�|�l��pO���=e+��cE�8يcz���{B��Sy	Hc��c�a_�yoi�GȠ$��2A��?����r�EҘ��˻�9?�d�hH���v�{���G���}���)7+a��jM��-~���k��1_�4Mc_�t����@Z�M�g�Jg\rYd���ؒ8�)#�YV��Gm��R�Q�g�hy�'��LLm�Ȗpy�t*����#|�,b-�Q-���SP���Il�w��<u�ȡK{p������F˶=���I|kg�wg�k*��sϮ��C�t�KK���W�M<�;_k2��N��+��>��V-�Q�/�zB���H�HH���_8�PC� ��"�4x)�#!��AL?�.�{�����#��	�oh�DZ�~C�i���`��Jm�ڑm��vNqA�(.�s��7 %U_Z~���$?�&f!a���fą�!��_O�+��6l� �\�YX�i<�ϵ��2�b�vg)}�<�f�ÓM+D� i��OR�n��>E�<��7�+�M�ކ��rc�ޅ�&q�o�?f��l��g3�x���=�l�������!j�k�@(���?~=Qc	���*J(
]{�]���r5�Wh�m������@P��3B������[�H�[iVL�-H��M�:�Ʀ�o��Y��ū��p��Cu��}����|!5���z�1V��c]�8ݠ���ߩx;j��+�Z��H ���d�8E'��@�:�ḷ���#ڡxu @���P4�`�`u3.��wR�@<���B ��`jԘ��>ŧqYj��R�R�m-ԿN�;Y�8�_�p��R�cc�����/ſ�8�f��s�r���>,��<��q�gr8���\��^��˄�i�U񬷈�*�y�\����3ʥ���p�s9�!��?j�c�>��}.��9�f��t%�^�a�N�ٸx���x�#��O֘�1����X0�s�F�"G�����;�hT�P;_,�ۊ�h0��#Q5��3�
<��o���>�'�����$Z&������0��3�9H+�:,��&Z��T��L��^Lqq����&��i�����\_��B�6a&? ��̺i�_L�n�_(��ȼ��)���_>�,�+���W�M���ځ2�����)����_!�q��G��������?e��,mp;h�4>�JM�!��N�W�����ϲ�w�W���������P�N���੯�UUy\���3�X� �Nk'Y�s:�\P���jX����T�<���3��,kh�<��opɥ�߳Y���X��L���fn�FzB��w 8Y�w�\�����w���	�r%Y���jOĂ):@� �	H�
��q�'�X�qQ ��u@����Ѽq��Z��v�u�����3tux��kZ�;��x��qݡ�_���'��w&�?릟W'���Un�����������3������ꜥ��(�֘��C�h&�>:����"��)��ϡrc)��b�_-1�+���b#e[ ���E�@���r$=����#��lFWh��5F������Tn�۳�H�K�P�����Eʪ��������=4?"�)��
˙;V��4=�ra�Dª!R�T�V�C�����Z�
O�#u��o(����#�_=��민V��;�p�߿��s�6ʃ(?[�:�+���y>��U�p��}۞��N���?����[�9��,�,��B�oX��h�r<d�ϗ-�ނ�m���E�k,p�"�(s�\�E�����/����B�K-��X���+�g#����:�q5�_���)Jo4�1UQ���٪��`o(�c���h$Hw8!�<İ�O!��k�{�m�ϲs١��E�EoQB�-�p(��b�	�bѶE7t��`'r��r���p<��,9�����Ų�WvT)֛���J��2�ţ���U���3�@E�<uej-�O�3l���i�&]c�6T��U F�h��Ez��2nN�ZK�O�~;�\H�����`W�Y�#{a���&��
#�c��;Ɋ��"Q%���x���`w78"����������D�6կkV\�*���y�b��v�]�Wq� ��v�W���v</��=���?��|2c��l/3W��l��Z{�_�]�u&���#�l�����ߔ3�*�.���{��o���f�?��vt�==�	�J��$?G��CE�9}?`�"��%:H��8=�[�ߝ��1?H����8���H0�*�r8�v��8�0�����O�Lp�\���J���9|��+��8
��9��� �ΐ�����b��(99�?��p~筎���E2��k#m>��7qx1����%���>��e>��8|����;9|��r�<�uY�uN�ǲ�?�����y��;w����Ay�B��m��e�����-��O�'��G�8Ϣ߀��Ƀ����kr��~�B&��O�S��n��w��:9J��?��;��1��p19@��������A���9�F������:��0TN:��+��!rR"�m���q���c��!q�߁��ɩ������������+Sm�-#y�8�\�T>9f}ʭ�+<��b��V��ߐy��Z����V�E�#ev@a����׀^��rrJ~���姧sd�~��qu���FP�:�S��1-��X�Kg��.yh�o�C[N�����k�p�f�bh�?o9f�m���([�}���I?C}C|���Ncw��җ����L����E�I��	�����le�;y�;*��#k~�����3���xw��؆4OXKҰ7?�a���A9r~�
���K�kKHYm���~L��1ߣ�%4��Oޯ��q݋����H���8�V�khw�By��q4.'���a�w\�r��G.�f���L�i\$��Z|{�Q�	��d�{���TL2r?�������������{���~����Y6�y{���`ƽD��։�\UL*Ku��LN�cjހ���� ����0<��5��3}�m>���A�Hņ�	\A���.���q�չ~���>�����4�<�!�|��6��9��	�J?3HO\�E��!�d�D� ��<j�s�c<Q2q1�2�5=<;YN5$�� 5�H��r{�v{�dט�l�-t\����SP
]�c����Nb�~�W{��P� ����� 4��P���gLDqd�������GT�~]rƇ��1a9"mߍ��AyN��n9Y6!G0K�.����5�]�Z����7�k�0���� ���~ 6�S2�9ooX3ooX�d�	w-ō��c�I_�Do�G��9k�_r*�5cE�`X3Tt"����8�	ә3���1�{�/�Zk�Β6�yP�j�b=���~u��5~(�b�`ů�ض�t���Z�M[w@n���b�Ț�"��nN�P�՜|���>�Q�<�B�pG˒��a�?�Ğ�8G]�z�ʷ$�iI�՘|�>5��}6y�o�����6�__����z��c �}�{���uY�uY�uY�u����h��{��`,�F$�@]q_o�	I�Dw0�:��R��/�b�(�kťt<g�J�vNΥ�� �ok�8;�R�ݘn�C*%�W�mL�b��)Lcz��}��`�ZLa�"��NL��a:�^*����J91mį7m�ވ)�G�t/]����,ƺ��U�d�y!�,���E-�J˛J+�(�yK�t��K�V-$���w�T
,Ztkܭ�5�~b[[I���o���9,��4��p�ذ����qx�rr�dӭ~����8�/��t��y��;A8X��/�ï��A����Oq�\̗��(N�т��uge�����f��~7��:��~�.��w���%?��y�p^�(����ҫ���^{si�=9�Ri$�[����R��ri�P��ҺHim}���t�Ri]i���u��d��}p��p-ͻ6߿j�{)����<�����h�7�;�V�Y�uY�uY�uY�uY�����v����a�uD�qFۄ��
�[8���v&d'=T��аsG�P?;s��̰�D�{��iy�x*J���{s�Kؙ'gg[Υ~v���ǟ��E��;���f�}��3H�I�L#��Ȩw�ggpX����0���_NS������������7xv�\t�>�(���J�Pz'�_��۔>A�~J_��5Jߧ4��빔^�.�;�vbw�n�����N���p�~߈��S�\���<���|����B���"�_�z�1�3M�p����d���v%F�T�x��a���S|�����v\d����sF|�>��
�������%�����4^�v���s�F|~fu�Z�g���oʿ�����|-I�l�\��\+y�,7��#	��w����B���2�+�=@�q	��@�]J'v�[�M��������[g���"���3������s��U}��A��Э&�֌��(��/��!��~���3۳6��Q�[).���$��v���=øT�D�B;?;�zf�8`;����/P|>��H��,��ƿ_���~�v8D���
��8��E<+�<�^�1O]�c���o� ���/���E\�����!�x^��������af����o���/�����[s���-�Z���j�&���s��^�[�3/OkWb�QI{;ծ3��vRA;"�_�3��'yZ<����xv��������Y���g9�Gv{�z�>��|s;�oZ�����gՇ�F�6_��"Z>si��[`޿����S`��?X�����C%����6��
�Ǉ
��G���#L������6�R�~��Pq�51��ݾ�P����K"� T�Ǫ��ns&�n	i7�)��ۊ�-qJ �߿�p>%}�eU�)�����X���nZ^��4�׷z�F02S����)(7�#�����8̐�� ?V�j
6Cuu�m�$w�)�^�a���F`偼G}́��
����Tښ:��+;]J[[G��8��V�N̬�;Vc�].�÷%���YJ5oıB%Ns
�����C���hK%ӧ6�3$#^z>A���e��X��aj����	��l�2��S�㮈5�f� ����h=���:[Xc�{��h9SI��݊������J;B�<Jo ��*Q��1<Z���Q��[��^Ţ��uM�r��c��+7t(��H�m�V6�b��P�O(ڀk���8�E݀V��Dv�SK,GM!y�TK�`���Po�{�s�{�O�������I�Y,��i��Lm3�����Yh�zg,��ѝ�+B
��B��"���!G`kǧQ5��l�N�<J�^=���@XE��ZD�%A�Җ�Q��bi���W�������;�p�m�������HT%��$��s�-����z3��ս ̉�x��2o�)ރ�P����l}�Q�$�p^��T*���:�,}��-.�m@�8�g�}����nv����x�[d�\a�P,��������!�A�@oB�9�uFFGQZ����mH+S&��#e��b����N���[�dt'?�D�$��,���C��?)ȳuPF˅���_�g��v���(s��AA��0Z"����F�M��������J�	A���2*��b��<[�et��/��_#�-���4��q�Z�E��v6�ɳu������GF�{��*_��^���?"�-�l]z�.�ԝ$�iA^�; �N"o���z�n*/�B-	���q��SI��*L�/����������T�[��T~��C0�B�p��%m����n���ۇ*Q>�.���J(� r  