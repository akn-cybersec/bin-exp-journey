#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<cctype>
#include<iomanip>

using namespace std;

string hexToAscii(string clean) {
    if (clean.length() >= 2 && (clean.substr(0, 2) == "0x" || clean.substr(0, 2) == "0X")) {
        clean = clean.substr(2);
    }
    
    if (clean.empty()) return "";

    if (clean.length() % 2 != 0) {
        clean = "0" + clean;
    }
    
    string bytes;
    for (size_t i = 0; i < clean.length(); i += 2) {
        try {
            string byteStr = clean.substr(i, 2);
            char byte = static_cast<char>(stoi(byteStr, nullptr, 16));
            bytes += byte;
        } catch (...) {
            continue; 
        }
    }
    
    reverse(bytes.begin(), bytes.end());
    
    string result;
    for (char c : bytes) {
        if (isprint(static_cast<unsigned char>(c))) {
            result += c;
        } else {
            result += '.';
        }
    }
    return result;
}

int main() {
    string line;
    cout<<"=========================================="<<endl;
    cout<<"      MULTI-HEX LITTLE-ENDIAN DECODER     "<<endl;
    cout<<"=========================================="<<endl;
    cout<<"Paste hex codes (space or pipe separated)"<<endl;
    cout<<"Type 'exit' to quit."<<endl<<endl;

    while (true) {
        cout << "> ";
        getline(cin, line);

        if (line == "exit" || line == "quit") break;
        if (line.empty()) continue;

        replace(line.begin(), line.end(), '|', ' ');
        replace(line.begin(), line.end(), '=', ' ');

        stringstream ss(line);
        string segment;
        
        cout<<endl<<left<<setw(15)<<"RAW HEX"<<" | "<<"DECODED (ASCII)"<<endl;
        cout<<"------------------------------------------"<<endl;

        while (ss >> segment) {
            if (segment.find('x') != string::npos || (segment.length() >= 4 && isxdigit(segment[0]))) {
                string decoded = hexToAscii(segment);
                if (!decoded.empty()) {
                    cout<<left<<setw(15)<<segment<<" | "<<decoded<<endl;
                }
            }
        }
        cout<<"------------------------------------------"<<endl<<endl;
    }

    cout<<"Exiting..."<<endl;
    return 0;
}