#include <bits/stdc++.h>
#if __has_include(<format>)
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif
using namespace std;
class javaString : public string {
   public:
    javaString(const string str) : string(str) {
    }
    int hash() {
        int n = 0, len = this->length();
        for (int i = 0; i < len; i++) {
            n = 31 * n + this->at(i);
        }
        return n;
    }
};
string s2hs(const string ostr) {
    javaString str(ostr);
    stringstream sstream;
    int hash = str.hash();
    sstream << ((hash < 0) ? "-" : "") << "0x" << hex << ((hash < 0) ? -hash : hash);
    return sstream.str();
}
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();  // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    const string output_path = "out/", input_path = "org", orignal_pkg_name = "com.kakao.talk", dist = "dist/";
    char pl = 'a';
    cout << dist << " 폴더 만드는 중... ";
    system(((string) "mkdir -p " + dist).c_str());
    cout << "완료\n";
    for (pl = 'a'; pl <= 'z'; pl++) {
        string pkg_name = "com.kakao.tal" + string(1, pl);
        string opt = output_path + pkg_name;
        cout << pkg_name << "의 클론을 시작했습니다.\n";
        cout << opt << " 폴더 만드는 중... ";
        system(((string) "mkdir -p " + opt).c_str());
        cout << "완료\n";
        cout << input_path << "에서 " << opt << "로 복사중... ";
        system(((string) "cp -r " + input_path + "/* " + opt).c_str());
        cout << "완료\n";
        cout << replaceAll(orignal_pkg_name, ".", "/") << "을 " << replaceAll(pkg_name, ".", "/") << "로 고치는 중... ";
        system(((string) "grep -r \"" + replaceAll(orignal_pkg_name, ".", "/") + "\" " + opt + " | awk '{split($1, result, \":\"); print result[1]}' | sort -u |xargs sed -i 's/" + replaceAll(orignal_pkg_name, ".", "\\/") + "/" + replaceAll(pkg_name, ".", "\\/") + "/g'").c_str());
        cout << "완료\n";
        cout << orignal_pkg_name << "을 " << pkg_name << "로 고치는 중... ";
        system(((string) "grep -r \"" + replaceAll(orignal_pkg_name, ".", "\\.") + "\" " + opt + " | awk '{split($1, result, \":\"); print result[1]}' | sort -u |xargs sed -i 's/" + replaceAll(orignal_pkg_name, ".", "\\.") + "/" + replaceAll(pkg_name, ".", "\\.") + "/g'").c_str());
        cout << "완료\n";
        string tmp = replaceAll(orignal_pkg_name, ".", "/"), tmp2 = replaceAll(pkg_name, ".", "/");
        for (int i = 1; i <= 6; i++) {
            if (i == 1) {
                cout << opt + "/smali/" + tmp << "을 " << opt + "/smali/" + tmp2 << "로 복사중... ";
                system(((string) "mv " + opt + "/smali/" + tmp + " " + opt + "/smali/" + tmp2).c_str());
                cout << "완료\n";
                continue;
            }
            cout << opt + "/smali_classes" + to_string(i) + "/" + tmp << "을 " << opt + "/smali_classes" + to_string(i) + "/" + tmp2 << "로 복사중... ";
            system(((string) "mv " + opt + "/smali_classes" + to_string(i) + "/" + tmp + " " + opt + "/smali_classes" + to_string(i) + "/" + tmp2).c_str());
            cout << "완료\n";
        }
        string gateway[] = {".notification.action.NEW_KALIM", ".notification.action.IN_APP_BROWSER", ".notification.action.NEW_MESSAGE", ".notification.action.FORWARD", ".notification.action.CHAT_LIST"};
        for (int i = 0; i < 5; i++) {
            cout << opt + "/smali_classes5/" + tmp2 + "/notification/NotificationGatewayActivity.smali"
                 << "에서 " << s2hs(orignal_pkg_name + gateway[i]) << "을 " << s2hs(pkg_name + gateway[i]) << "로 고치는 중... ";
            system(((string) "sed -i -e 's/" + s2hs(orignal_pkg_name + gateway[i]) + "/" + s2hs(pkg_name + gateway[i]) + "/' " + opt + "/smali_classes5/" + tmp2 + "/notification/NotificationGatewayActivity.smali").c_str());
            cout << "완료\n";
        }
        string action[] = {".notification.REPLY_MESSAGE", ".notification.READ_MESSAGE"};
        for (int i = 0; i < 2; i++) {
            cout << opt + "/smali_classes5/" + tmp2 + "/notification/NotificationActionService.smali"
                 << "에서 " << s2hs(orignal_pkg_name + action[i]) << "을 " << s2hs(pkg_name + action[i]) << "로 고치는 중... ";
            system(((string) "sed -i -e 's/" + s2hs(orignal_pkg_name + action[i]) + "/" + s2hs(pkg_name + action[i]) + "/' " + opt + "/smali_classes5/" + tmp2 + "/notification/NotificationActionService.smali").c_str());
            cout << "완료\n";
        }
        cout << "앱이름을 카카오톡" + string(1, pl) + "로 변경 중... ";
        system(((string) "sed -i -e 's/카카오톡/카카오톡" + string(1, pl) + "/g' " + opt + "/res/values-ko/strings.xml").c_str());
        cout << "완료\n";
        cout << "빌드 시작\n";
        system(((string) "cd " + opt + ";java -jar apktool.jar b --use-aapt2;").c_str());
        cout << "빌드 끝\n";
        cout << "서명 시작\n";
        system(((string) "cd " + opt + ";(echo \"비번\"|jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore some.keystore ./dist/*.apk someting) > /dev/null;").c_str());
        cout << "서명 끝\n";
        cout << opt + "/dist/*" << "를 ./" + dist + pkg_name + ".apk" << "로 복사중... ";
        system(((string) "cp " + opt + "/dist/* ./" + dist +  pkg_name + ".apk").c_str());
        cout << "완료\n";
        cout << "작업 폴더 비우는 중... ";
        system(((string) "rm -rf " + opt).c_str());
        cout << "완료\n";
        cout << pkg_name << "의 클론이 끝났습니다.\n";
    }
    return 0;
}
