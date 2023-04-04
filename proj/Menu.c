#include <lcom/lcf.h>
#include "Menu.h"



enum MenuOption Option;

int highscore;
Sprite *menu;

Sprite *cursor;

Sprite *HS;

Sprite* zero;

Sprite* um;

Sprite* dois;

Sprite* tres;

Sprite* quatro;

Sprite* cinco;

Sprite* seis;

Sprite* sete;

Sprite* oito;

Sprite* nove;

Enemies *en;

Spaceship *sps;

Defenses *df;




//static bool button_pressed = false;

//Variaveis Keyboard

uint32_t scancode;

bool make, ValidScanCode;

uint8_t size;

uint8_t bytes[2];


//Variaveis Mouse

struct packet pp;

uint8_t counter_bytes;

bool valid_byte;

uint8_t byte_packet[3];

uint32_t counter;

uint8_t scancode_mouse;


void Create_Menu_Sprites() {

  menu = create_sprite(MenuSpaceInvaders, 0, 0, 0, 0);

  cursor = create_sprite(cursor_xpm, 0, 0, 0, 0);

  HS = create_sprite(Highscore_xpm , 50 , 800 , 0 ,0);

}

void load_menu_sprites()
{
  print_sprite(menu);
  print_sprite(cursor);
  print_sprite(HS);

  print_score(220 , 820 ,highscore);
}

void create_time_sprites(int x , int y)
{
  zero = create_sprite(zero_xpm , x , y ,0 ,0);

  um = create_sprite(um_xpm , x , y ,0 ,0);

  dois = create_sprite(dois_xpm , x , y ,0 ,0);

  tres = create_sprite(tres_xpm , x , y ,0 ,0);

  quatro = create_sprite(quatro_xpm , x , y ,0 ,0);
  
  cinco = create_sprite(cinco_xpm , x , y ,0 ,0);

  seis = create_sprite(seis_xpm , x , y ,0 ,0);

  sete = create_sprite(sete_xpm , x , y ,0 ,0);

  oito = create_sprite(oito_xpm , x , y ,0 ,0);

  nove = create_sprite(nove_xpm , x , y ,0 ,0);
}

void destroy_time_sprites()
{

  destroy_sprite(zero);

  destroy_sprite(um);

  destroy_sprite(dois);

  destroy_sprite(tres);

  destroy_sprite(quatro);

  destroy_sprite(cinco);

  destroy_sprite(seis);

  destroy_sprite(sete);

  destroy_sprite(oito);

  destroy_sprite(nove);
}

void print_hours()
{
  int x = 800 ,y =  800;

  create_time_sprites(x,y);

  uint8_t hours = day_time[2];
  if(hours < 10) //to see if hours is one digit
  {
    print_sprite(zero);


    switch(hours)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
   
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);
  
        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);
    
        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);
 
        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);
  
        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);
   
        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);
  
        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);
   
        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);
 
        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);
        break;       
    }


  }

  else
  {

    int first_digit = hours % 10;

    int second_digit = hours / 10;

    switch(second_digit)
    {
      case 0:
        print_sprite(zero);
    
        break;

      case 1:
        print_sprite(um);
     
        break;

      case 2:
        print_sprite(dois);
    
        break;
      case 3:
        print_sprite(tres);

        break;

      case 4:
        print_sprite(quatro);

        break;

      case 5:
        print_sprite(cinco);
  
        break;
      case 6:
        print_sprite(seis);

        break;
      case 7:
        print_sprite(sete);
   
        break;
      case 8:
        print_sprite(oito);
 
        break;
      case 9:
        print_sprite(nove);
 
        break;       
    }

    switch(first_digit)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
 
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);
   
        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);

        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);
   
        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);
  
        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);
     
        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);

        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);
  
        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);

        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);

        break;       
    }

  }




}


void print_minutes()
{
  int x = 850 ,y =  800;

  create_time_sprites(x,y);

  uint8_t minutes = day_time[1];
  if(minutes < 10) //to see if hours is one digit
  {
    print_sprite(zero);

    switch(minutes)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);
        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);
        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);
        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);
        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);
        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);
        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);
        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);
        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);
        break;       
    }


  }

  else
  {

    int first_digit = minutes % 10;

    int second_digit = minutes / 10;

    switch(second_digit)
    {
      case 0:
        print_sprite(zero);
        break;

      case 1:
        print_sprite(um);
        break;

      case 2:
        print_sprite(dois);
        break;
      case 3:
        print_sprite(tres);
        break;

      case 4:
        print_sprite(quatro);
        break;

      case 5:
        print_sprite(cinco);
        break;
      case 6:
        print_sprite(seis);
        break;
      case 7:
        print_sprite(sete);
        break;
      case 8:
        print_sprite(oito);
        break;
      case 9:
        print_sprite(nove);
        break;       
    }

    switch(first_digit)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);
        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);
        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);
        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);
        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);
        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);
        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);
        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);
        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);
        break;       
    }

  }




}

void print_seconds()
{
  int x = 900 ,y =  800;

  create_time_sprites(x,y);

  uint8_t seconds = day_time[0];
  if(seconds < 10) //to see if hours is one digit
  {
    print_sprite(zero);

    switch(seconds)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);
        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);
        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);

        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);
        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);
        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);

        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);

        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);

        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);

        break;       
    }


  }

  else
  {

    int first_digit = seconds % 10;

    int second_digit = seconds / 10;

    switch(second_digit)
    {
      case 0:
        print_sprite(zero);

        break;

      case 1:
        print_sprite(um);

        break;

      case 2:
        print_sprite(dois);

        break;
      case 3:
        print_sprite(tres);
        break;

      case 4:
        print_sprite(quatro);
        break;

      case 5:
        print_sprite(cinco);

        break;
      case 6:
        print_sprite(seis);

        break;
      case 7:
        print_sprite(sete);

        break;
      case 8:
        print_sprite(oito);

        break;
      case 9:
        print_sprite(nove);

        break;       
    }

    switch(first_digit)
    {
      case 0:
        zero->x = zero->x + 17;
        print_sprite(zero);
 
        break;

      case 1:
        um->x = um->x + 17;
        print_sprite(um);

        break;

      case 2:
        dois->x = dois->x + 17;
        print_sprite(dois);

        break;
      case 3:
        tres->x = tres->x + 17;
        print_sprite(tres);

        break;

      case 4:
        quatro->x = quatro->x + 17;
        print_sprite(quatro);

        break;

      case 5:
        cinco->x = cinco->x + 17;
        print_sprite(cinco);

        break;
      case 6:
        seis->x = seis->x + 17;
        print_sprite(seis);

        break;
      case 7:
        sete->x = sete->x + 17;
        print_sprite(sete);

        break;
      case 8:
        oito->x = oito->x + 17;
        print_sprite(oito);
  
        break;
      case 9:
        nove->x = nove->x + 17;
        print_sprite(nove);

        break;       
    }

  }


}


void print_time()
{
  print_hours();


  print_minutes();


  print_seconds();

}

void handle_NewGame()
{

  en = create_enemies(10);
  sps = create_spaceship(0, 20);
  df = create_defenses(15);

  game(sps, en, df, 20);

  scancode = 0;

  load_Menu(30);



}


void handle_Help()
{

  scancode = 0;
  int ipc_status;
  message msg;
  uint8_t kbd_int_bit = IRQ1;
  //This function is called when the user presses the Help button on the Menu

  //When the user presses the ESC KEY he returns to the menu


  vg_clear_screen(); //Clear the menu screen

  Sprite *help = create_sprite(Help_xpm , 0 , 0 , 0 , 0);

  print_sprite(help); //Print the sprite to the secundary buffer

  double_buff(); //print the help sprite to the main buffer

  unsigned long res;

  

  kbd_subscribe_int(&kbd_int_bit);

  //COLOCAR O SCANCODE A 0 DEPOIS

    while(scancode != ESC_KEY) { 
        //subscribe interruption
        
        /* Get a request message. */
        if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
        printf("driver_receive failed with: %lu", res);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE :                              /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & BIT(kbd_int_bit)) {

                      kbd_ih();
                      if(ValidScanCode)
                      {
                        ValidScanCode = false; 
                      }                  

                    }
                    break;
                default:  
                    break; /* no other notifications expected: do nothing */

            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }

    kbd_unsubscribe_int();

    scancode = 0;


    load_Menu(30);
}

void handle_option(enum MenuOption Option)
{

  switch(Option)
  {

    case NewGame:
      handle_NewGame();
      break;

    case Help:
      handle_Help();
      break;

    case Quit:
      break;

    case  NoOption:
      break;

  }

  

}


void check_collisions()
{

  struct mouse_ev * mouse_event = mouse_detect_event_v2();

  
  /*
  if(mouse_event->type == LB_PRESSED)
  {
    //NewGame
    if(cursor->x > 380 &&  cursor->x < 765 && cursor->y > 375 && cursor->y < 450)
    {
      button_pressed = true;
    }
    //Help
    else if(cursor->x > 465 && cursor->x < 655 && cursor->y > 485 && cursor->y < 550)
    {
      button_pressed = true;
    }
    //Quit
    else if(cursor->x > 470 && cursor->x < 650 && cursor->y > 595 && cursor->y < 655)
    {
      button_pressed = true;
    }

    return;
  }

  */
  if(mouse_event->type == LB_RELEASED)
  {
    //NewGame
    if(cursor->x > 380 &&  cursor->x < 765 && cursor->y > 375 && cursor->y < 450)
    {
      //button_pressed = false;
      Option = NewGame;
    }
    //Help
    else if(cursor->x > 465 && cursor->x < 655 && cursor->y > 485 && cursor->y < 550)
    {
      //button_pressed = false;
      Option = Help;
    }
    //Quit
    else if(cursor->x > 470 && cursor->x < 650 && cursor->y > 595 && cursor->y < 655)
    {
      //button_pressed = false;
      Option = Quit;
    }

    return;

  }




  //button_pressed = false;


}











void load_Menu(uint8_t fr_rate) {


  Option = NoOption;

  bool tf = false;

  uint8_t frc = 60 /fr_rate;

  int ipc_status;

  message msg;

  uint8_t bit_no_mouse = IRQ12;

  uint8_t bit_no_rtc = 8;

  uint8_t bit_no_timer = 0;
 
  unsigned long res;

  vg_clear_screen();

  Create_Menu_Sprites();
  /////////////////////////////////////////////////////////////////


  if(highscore < score)
  {
    highscore = score;
  }
  //////////////////////////////////////////////////////////////////
  score = 0;
   //enable rtc
  if (mouse_enable_data_reporting_v2() != 0) {
    printf("Could not enable the data report \n");
    return ;
  }



  if (mouse_subscribe_int(&bit_no_mouse)) {
    printf("[ERROR] Did not subscribed the interrupts\n");
    return ;
  }

  timer_subscribe_int(&bit_no_timer);

  rtc_subscribe_int(&bit_no_rtc);

  //enable();


  while (Option == NoOption) {
    if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %lu", res);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if(msg.m_notify.interrupts & BIT(bit_no_rtc))
          {
            rtc_ih();

          }
          if (msg.m_notify.interrupts & BIT(bit_no_mouse)) {

            valid_byte = true;

            mouse_ih();

            if (valid_byte) {

              if (counter_bytes == 0 && (scancode_mouse & BIT(3))) {
                byte_packet[0] = scancode_mouse;
                counter_bytes++;
                continue;
              }

              if (counter_bytes == 1) {
                byte_packet[1] = scancode_mouse;
                counter_bytes++;
                continue;
              }

              if (counter_bytes == 2) {

                byte_packet[2] = scancode_mouse;

                PacketParsing();

                check_collisions();

                move_cursor(cursor , pp.delta_x , pp.delta_y);
                
                counter_bytes = 0;
                continue;
              }
            }
          }


          if(msg.m_notify.interrupts & BIT(bit_no_timer))
          {

            print_time();


            timer_int_handler();
            if (counter % frc == 0) //FREQUENCIA DEFINIDA A 60 HZ , 60 VEZES POR SEGUNDO
            {
              if (tf) {
                double_buff();
                vg_clear_screen();
              }
              tf = true;
              load_menu_sprites();
              
            }
          

          }


          break;
        default:
          break;
      }
    }
    else {
    }
  }

  counter = 0;

  mouse_unsubscribe_int();

  timer_unsubscribe_int();

  rtc_unsubscribe_int();

 
  if (mouse_disable_data_reporting() != 0) {
    printf("[ERROR] Did not return the mouse to the initial state\n");
    return ;
  }


  handle_option(Option);

}


