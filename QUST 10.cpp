//#playfair matrix
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to create a Playfair matrix from a key
void createPlayfairMatrix(char *key, char matrix[5][5]) {
    int len = strlen(key);
    int index = 0;
    int i, j;
    int alphabet[26] = {0}; // Mark which letters of the alphabet are used
    // Fill the matrix with the key
    for (i = 0; i < len; i++) {
        char c = toupper(key[i]);
        if (c == 'J') // Replace 'J' with 'I'
            c = 'I';
        if (!alphabet[c - 'A']) {
            matrix[index / 5][index % 5] = c;
            alphabet[c - 'A'] = 1;
            index++;
        }
    }
    // Fill the remaining matrix with the alphabet (excluding 'J')
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !alphabet[c - 'A']) {
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char *plaintext, char matrix[5][5]) {
    int len = strlen(plaintext);
    int i;
    for (i = 0; i < len; i += 2) {
        char a = toupper(plaintext[i]);
        char b = toupper(plaintext[i + 1]);
        int row_a, col_a, row_b, col_b;
        // Find positions of characters a and b in the matrix
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (matrix[row][col] == a) {
                    row_a = row;
                    col_a = col;
                }
                if (matrix[row][col] == b) {
                    row_b = row;
                    col_b = col;
                }
            }
        }
        // Encrypt the pair based on positions in the matrix
        if (row_a == row_b) { // Same row
            printf("%c%c", matrix[row_a][(col_a + 1) % 5], matrix[row_b][(col_b + 1) % 5]);
        } else if (col_a == col_b) { // Same column
            printf("%c%c", matrix[(row_a + 1) % 5][col_a], matrix[(row_b + 1) % 5][col_b]);
        } else { // Forming rectangle
            printf("%c%c", matrix[row_a][col_b], matrix[row_b][col_a]);
        }
    }
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char matrix[5][5];
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    // Create Playfair matrix from the key
    createPlayfairMatrix(key, matrix);

    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nEncrypted Message: ");
    encryptPlayfair(plaintext, matrix);
    printf("\n");

    return 0;
}