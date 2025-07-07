A simple C++ terminal-based password generator that creates secure passwords and saves them to a file with timestamps.

Features

Generates random passwords with customizable length
Includes lowercase, uppercase, digits, and symbols
Saves passwords to passwords.txt with:

Category (e.g., "Google", "Steam")

Login/username

Timestamp

Lightweight and runs on Linux (tested on Garuda Sway)

How to Use

  Compile:

g++ -std=c++17 -o password_generator password_generator.cpp

Run:

  ./password_generator

  Follow prompts to:

  Enter a category (e.g., "Email")

  Enter a login/username

  Get a generated password (saved automatically)

Example Output (passwords.txt)

[Google]  
Time: 2024-05-20 14:30:22  
Login: user123  
Password: xY7#kL9*pQ!  

Dependencies

  C++17 compiler (g++)

  Linux (uses <random>, <fstream>, etc.)

Customization

Modify the generate_password() function to:

  Change default length (currently 12)

  Exclude symbols (set use_special = false)

Note: For security, avoid using this for real passwords without further encryption.

Feel free to improve or add features (e.g., CLI args, encryption)!
