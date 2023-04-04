#include "GAme.h"

int score = 0;

int arr[5]; //Score

int num_dig = 0;
bool shoot  = false;
bool sp_shot_in = false;
bool en_shot_in = false;
bool final = false;
bool win = false;



int num_enemies = 50;

int video_rectangle(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {



  if (vg_draw_rectangle(x, y, width, height, color) != 0) {
    vg_exit();
    printf("[ERROR] could not draw the rectangle\n");
    return 1;
  }


  return 0;
}

int video_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint8_t row;
  uint8_t col;
  uint16_t x = 0, y = 0, width = 0, height = 0;
  uint32_t color;


  get_rect_dimensions(no_rectangles, &width, &height);

  if (vg_draw_rectangle(0, 0, width, height, first) != 0) {
    vg_exit();
    printf("[ERROR] could not draw the rectangle\n");
    return 1;
  }

  col = 1;
  row = 0;
  x += width;
  //y=0;
  if (col >= no_rectangles) {
    col = 0;
    x = 0;
    row++;
    y += height;
  }

  while (row < no_rectangles) {
    if (mode == INDEXED_COLOR_MODE) {
      color = index_mode(row, col, no_rectangles, step, first);
    }
    else {
      color = get_color_direct(row, col, step, first);
    }

    if (vg_draw_rectangle(x, y, width, height, color) != 0) {
      vg_exit();
      printf("[ERROR] could not draw the rectangle\n");
      return 1;
    }
    col++;
    x += width;
    if (col >= no_rectangles) {
      col = 0;
      x = 0;
      row++;
      y += height;
    }
  }

  return 0;
}



void button_pressed()
{

  struct mouse_ev * mouse_event = mouse_detect_event_v2();


  if(mouse_event->type==LB_PRESSED)
  {


    shoot = true;

    return;

  }


  return;

}



bool check(Sprite* sp , uint32_t color)
{

 
  
  for (int16_t j = (sp->y); j < ((sp->y) + (sp->height)); j++) {
    for (int16_t i = (sp->x); i < ((sp->x) + (sp->width)); i++) {


      int pos = (j * gethres())  + i;
    
      if(check_pixel(pos, color))
      {
        return true;
      }
    }
  }

  return false;

}



void collision_shot(Spaceship *sp , Enemies *en)
{
  int i , j;
  bool exists = false;


  if(final)
  {
    if((sp->spshot->shot->y < 50) && 
    (((sp->spshot->shot->x + sp->spshot->shot->width/2) > en->ds->sp->x + en->ds->sp->width/2 - 10 )&&
    ((sp->spshot->shot->x + sp->spshot->shot->width/2) < en->ds->sp->x + en->ds->sp->width/2 + 10 )))
    {
      en->ds->life = en->ds->life - 10;
      sp_shot_in = false;
    }
    return;
  }
  for(i = 0 ;  i < 5 ; i++)
  {
    for(j = 0 ; j < 10 ; j++)
    {

      if(en->tief[i][j]->life&&check(en->tief[i][j]->sp , 0x3DE4D2))
      {
        en->tief[i][j]->life = false;
        sp_shot_in = false;
        num_enemies--;
        score++;
        exists = true;
        break;
        
        
      }


    }

    if(exists)
      break;

  }


}

void collision_en_shot(Spaceship *sp  , Defenses *def, Enemies *en)
{

  for(int i = 0; i < 4 ; i++)
  {

    if(def->def[i]->life > 0 && check(def->def[i]->sp1 ,0xE11515))
    {
      def->def[i]->life--;
      en_shot_in = false;
    }

  }

  if(sp->life > 0 && check(sp->sp,0xE11515))
  {
    sp->life -= 5;
    en_shot_in = false;
  }

}

void create_score_sprites(int x , int y)
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


void getScoreArr(uint8_t score)
{
  int num;
      while (score != 0) { 
  
        // Extract the last digit of N 
        num = score % 10; 
  
        // Put the digit in arr[] 
        arr[num_dig] = num; 
        num_dig++; 
  
        // Update N to N/10 to extract 
        // next last digit 
        score = score / 10; 
    } 
}

int getScore()
{
  return score;
}

void print_score(int x , int y , int score_x)
{

  uint8_t digit , incremento = 0;

  int score_copy = score_x;

  create_score_sprites(x ,y);

  getScoreArr(score_copy);

  for(int i = 0  ; i < num_dig ; i++)
  {
    digit = arr[i];

    switch(digit)
    {
      case 0:
        zero->x = zero->x - incremento;
        print_sprite(zero);
   
        break;

      case 1:
        um->x = um->x - incremento;
        print_sprite(um);
  
        break;

      case 2:
        dois->x = dois->x - incremento;
        print_sprite(dois);
    
        break;
      case 3:
        tres->x = tres->x - incremento;
        print_sprite(tres);
 
        break;

      case 4:
        quatro->x = quatro->x - incremento;
        print_sprite(quatro);
  
        break;

      case 5:
        cinco->x = cinco->x - incremento;
        print_sprite(cinco);
   
        break;
      case 6:
        seis->x = seis->x - incremento;
        print_sprite(seis);
  
        break;
      case 7:
        sete->x = sete->x - incremento;
        print_sprite(sete);
   
        break;
      case 8:
        oito->x = oito->x - incremento;
        print_sprite(oito);
 
        break;
      case 9:
        nove->x = nove->x - incremento;
        print_sprite(nove);
        break;       
    }

    incremento+=17;
  }

  num_dig = 0;


}

void game(Spaceship *sp, Enemies *en, Defenses *def, uint8_t fr_rate)
{

  num_enemies = 50;

  win = false;

  final = false;

  sp->life = 200;

  Deathstar *ds; 

  int ipc_status;
  message msg;
  uint8_t kbd_int_bit = IRQ1;
  uint8_t bit_no = TIMER0_IRQ;
  uint8_t bit_no_mouse = IRQ12;

  Sprite *bg = create_sprite(background, 0, 0, 0, 0);

  Sprite *GameOver = create_sprite(GameOver_xpm , 300 , 200 ,0 ,0);

  Sprite *win_image  = create_sprite(Win_xpm , 300 , 200 ,0 ,0);

  ds = create_ds(200, 10);

  int res;

  

  uint8_t frc = 60 / fr_rate;


  sp_shot_in = false;
  en_shot_in = false;



  if (mouse_enable_data_reporting_v2() != 0) {
    printf("Could not enable the data report \n");
    return ;
  }

  kbd_subscribe_int(&kbd_int_bit);

  timer_subscribe_int(&bit_no);


  mouse_subscribe_int(&bit_no_mouse);

  uint16_t counterframe = 0;

  vg_clear_screen();

  while (scancode != ESC_KEY) {
    //subscribe interruption
    // Get a request message.
    if ((res = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", res);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { //received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & BIT(kbd_int_bit)) {

            kbd_ih();

            if (ValidScanCode)
              ValidScanCode = false;
            else
              return;
          }
          if (msg.m_notify.interrupts & BIT(bit_no)) {

            if (timercounter % frc == 0) //FREQUENCIA DEFINIDA A 60 HZ , 60 VEZES POR SEGUNDO
            {


              double_buff();
              vg_clear_screen();

              //video_pattern(0x14c, 32, 2, 1);
              print_sprite(bg);
              print_score(100 ,0 ,score);
              print_sp(sp);
              print_defenses(def);
              print_enemies(en);


              if(sp->life > 0 && !win)
              {
                if (en_shot_in) {
                  print_enshot(en->ens);
                }
              
                if (sp_shot_in) {
                  print_spshot(sp->spshot);
                }
              
                if(en->final && en->ds->life >0){
                  uint8_t R = (1 - ((float) en->ds->life/20)) * 0xFF;
                  uint8_t B = ((float) en->ds->life/20) * 0xFF;
                  uint32_t color = R << 16 | B;
              
                  vg_draw_rectangle(  gethres() - 150 - 10, 30, 150,10, 0);
                  vg_draw_rectangle(  gethres() - 150 - 10, 30, ((float)en->ds->life/20)*150,10, color);
  
                }
                
                uint8_t R = (1 - ((float) sp->life/200)) * 0xFF;
                uint8_t G = ((float) sp->life/200) * 0xFF;
                uint32_t color = R << 16 | G << 8;
             
                vg_draw_rectangle( gethres() - 150 - 10, 10, 150,10, 0);
                vg_draw_rectangle( gethres() - 150 - 10, 10, ((float)sp->life/200)*150,10, color);

                if(shoot && !sp_shot_in)
                {
                  sp_shoot(sp);

                  sp_shot_in = true;

                  shoot = false;
                }
              
                if(sp_shot_in)collision_shot(sp , en);


                if(!en_shot_in && !en->final) {
                  en_shoot(en);
                  en_shot_in = true;
                }
                
                //FINAL
                if (num_enemies <= 0 && !final) {
                  en->final = true;
                  en->ds = ds;
                  final = true;
                  en->ds->life = 20;
                  en_shot_in = false;
                  counterframe = 0;
                }

                if(en_shot_in)collision_en_shot(sp , def,en);

              

                counterframe++;

                if(!changepos_kb(en, counterframe))
                {
                  sp->life = 0;
                }

                if(en->final)
                {
                  if(counterframe <30*5)
                    changepos_ds(ds);
                  else if(counterframe>= 30*7)
                    counterframe = 0;
                }

                if (scancode == A) {
                  changepos_kbn(sp, counterframe);
                }

                if (scancode == D) {
                  changepos_kbp(sp, counterframe);
                }
                if (sp_shot_in) {
                  if (!move_spshot(sp->spshot)) {
                    sp_shot_in = false;
                  }
                }
                if (en_shot_in) {
                  if (!move_enshot(en->ens)) {
                    en_shot_in = false;
                  }
                }


                if(en->final && en->ds->life == 0)
                {
                  win = true;
                }

              }

              else{

                if(win)
                {
                  print_sprite(win_image);
                }
                else{
                  print_sprite(GameOver);
                }

              }


              

            }

            
            
            timercounter++;
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

                button_pressed();
                
                counter_bytes = 0;
                continue;
              }
            }
          }


          break;



        default:
          break;
      }
         
    }
    
  }

  kbd_unsubscribe_int();

  timer_unsubscribe_int();

  mouse_unsubscribe_int();

  if (mouse_disable_data_reporting() != 0) {
    printf("[ERROR] Did not return the mouse to the initial state\n");
    return ;
  }

  timercounter = 0;


}
