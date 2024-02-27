#include <stdio.h>
#include <ctype.h>

void encrypt(char message[], int key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = ((message[i] - base + key) % 26) + base;
        }
    }
}

void decrypt(char message[], int key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = ((message[i] - base - key + 26) % 26) + base;
        }
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key (0-25): ");
    scanf("%d", &key);

    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    decrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}