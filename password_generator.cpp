#include <iostream>
#include <string>
#include <../random>
#include <../algorithm>
#include <../cctype>
#include <../ctime>
#include <../iomanip>
#include <../fstream>

// Check if password contains at least one char from each selected set
bool is_valid_password(const std::string& password, bool use_upper, bool use_digits, bool use_special) {
    bool has_lower = false;
    bool has_upper = false;
    bool has_digits = false;
    bool has_special = false;

    for (char c : password) {
        if (islower(c)) has_lower = true;
        else if (isupper(c)) has_upper = true;
        else if (isdigit(c)) has_digits = true;
        else has_special = true;
    }

    // Enforce rules for enabled charset
    if (use_upper && !has_upper) return false;
    if (use_digits && !has_digits) return false;
    if (use_special && !has_special) return false;

    return true;
}


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
    int max_attempts = 10; // Prevent loops
    for (int attempt = 0; attempt < max_attempts; ++attempt) {
        for (int i = 0; i < length; ++i) {
            password += charset[distribution(generator)];
        }

    if (is_valid_password(password, use_upper, use_digits, use_special)) {
        return password; // Valid password
    }

    }

    std::cerr << "Failed to generate a valid password after " << max_attempts << "attempts.\n";
    return "";

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
    bool use_upper = true, use_digits = true, use_special = true;

    std::cout << "Enter category (e.g., 'Discord', 'Steam'): ";
    std::getline(std::cin, category);

    std::cout << "Enter login/username: ";
    std::getline(std::cin, login);

    std::string password = generate_password(length, use_upper, use_digits, use_special);
    std::cout << "Generated Password: " << password << "\n";

    save_to_file(category, login, password);
    return 0;
}
