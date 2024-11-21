/Applications/Android\ Studio.app/Contents/jbr/Contents/Home/bin/keytool \
    -genkeypair -dname "cn=myname, ou=mygroup, o=mycompany, c=mycountry" -keyalg rsa \
    -alias android -keypass android -storepass android \
    -keystore example.keystore -validity 1800
