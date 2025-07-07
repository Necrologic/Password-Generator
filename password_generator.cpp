#include <iostream>
#include <string>
#include <../random>
#include <../algorithm>
#include <../climits>
#include <../iomanip>
#include <../fstream>


std::string generate_password(int length, bool use_upper, bool use_digits, bool use_special) {
    const std::string lower = "abcdefghijklmnopqrstuvwxyz";
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string special = "!@#$^&()*-+=[]{};:,.<>?";

    std::string charset = lower;
    if (use_upper) charset += upper;
    if (use_digits) charset += digits;
    if (use_special) charset += special;

    if (charset.empty()) {
        std::cerr << "Error: No character set selected!\n";
        return "";
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, charset.size() - 1);

    std::string password;
    for (int i = 0; i < length; ++i) {
        password += charset[distribution(generator)];
    }

    return password;
}

void save_to_file(const std::string& category, const std::string& login, const std::string& password) {
    std::ofstream file("passwords.txt", std::ios::app); // Append mode
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!\n";
        return;
    }

    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Write to file
    file << "[" << category << "]\n";
    file << "Time: " << timestamp << "\n";
    file << "Login: " << login << "\n";
    file << "Password: " << password << "\n";
    file.close();

    std::cout << "Saved to passwords.txt!\n";
}

int main () {
    std::string category, login;
    int length = 12;

    std::cout << "Enter category (e.g., 'Google', 'Steam'): ";
    std::getline(std::cin, category);

    std::cout << "Enter login/username: ";
    std::getline(std::cin, login);

    std::string password = generate_password(length, true, true, true);
    std::cout << "Generated Password: " << password << "\n";

    save_to_file(category, login, password);
    return 0;
}