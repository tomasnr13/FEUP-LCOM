#include "GAme.h"


enum MenuOption{NewGame , Help , Quit  , NoOption};

void load_Menu(uint8_t fr_rate);

void Create_Menu_Sprites();

void load_menu_sprites();

void handle_NewGame();

void handle_Help();

void print_time();

void handle_option(enum MenuOption Option);

void check_collisions();

void print_hours();

void print_minutes();

void print_seconds();


