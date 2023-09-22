#include <iostream>
#include <string>

int main() {
    std::string test = "eééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééééé";

    std::cout << test.length() << std::endl;
    while (test.length() > 510) {
        std::string res = test.substr(0, 510);
        test.erase(0, 510);

        int lastCharBytes = 0;
        int i = res.length() - 1;

        // Trouver le dernier caractère complet en parcourant à partir de la fin
        while (i >= 0 && (res[i] & 0xC0) == 0x80) {
            ++lastCharBytes;
            --i;
        }

        if (lastCharBytes > 0) {
            // Le dernier caractère a été tronqué, ajuster la taille de la sous-chaîne
            res.erase(res.length() - lastCharBytes);
            test.insert(0, res.substr(res.length()));
        }

        std::cout << "Res: " << res << " length :" << res.length() << std::endl;
    }

    if (!test.empty()) {
        std::cout << "Sous-chaîne restante: " << test << std::endl;
    }

    return 0;
}