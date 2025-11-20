#ifndef CONTROL_H
#define CONTROL_H
void clear_input_buffer();
void menu_choice();
void exit_program();
int get_valid_choice(int min, int max);
int is_id_card_valid(char *id_card);
int is_username_valid(char *username);
int is_password_valid(char *password);
int clear_file(const char *filename);
#endif
