
#include "graphic.h"

#include "graphic_consts.h"

//VARIAVEIS GLOBAIS

static int bytes_per_pixel;

static int h_res, v_res;

static void *video_mem; //FRAME BUFFER VIDEO MEM ENDERE�O

static vbe_mode_info_t vmi_p;

static uint16_t pixwidth, pixheight;

/*int set_mode_graphic(uint16_t mode) {
  struct reg86 r;
  memset(&r, 0, sizeof(reg86));
  r.ax = 0x4F02;
  r.bx = 1 << 14 | mode;
  r.intno = 0x10;
  if (sys_int86(&r) != OK) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }
  return 0;
}

int map_vram(uint16_t mode) {
  struct minix_mem_range mr;
  unsigned int vram_base; 
  unsigned int vram_size; 
  int r;	

  if (vbe_get_mode_info(mode, &vmi_p) != 0) {
    return 1;
  }

  vram_base = vmi_p.PhysBasePtr;
  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bytes_per_pixel = vmi_p.BitsPerPixel / 8;
  vram_size = h_res * v_res * bytes_per_pixel;

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    panic("couldn't map video memory");
    return 1;
  }
  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (int i = x; i < x + len; i++) {
      if (color_pixel(i, y, color) != 0) {
        printf("color pixel failed!\n");
        return 1;
      }
    }
    return 0;
}

int color_pixel(uint16_t x, uint16_t y, uint32_t color) {
  uint8_t *pointer;

  if (x < 0 || x > h_res) {
    printf("[ERROR] X out of index \n");
    return 1;
  }

  if (y < 0 || y > v_res) {
    printf("[ERROR] Y out of index \n");
    return 1;
  }

  pointer = (unsigned char *) video_mem;

  uint8_t aux = 0xFF;
  uint8_t cp;
  for (int i = 0; i < bytes_per_pixel;i++) {
    cp = color & aux;
    *(pointer+ y * h_res * bytes_per_pixel + x * bytes_per_pixel + i) = cp;
    color = color >> 8;
  }
  return 0;
}

int print_xpm(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm, XPM_INDEXED, &img);
  if (map == NULL) {
    return 1;
  }

  pixwidth = img.width;
  pixheight = img.height;

  for (uint16_t j = y; j < y + pixheight; j++) {
    for (uint16_t i = x; i < x + pixwidth; i++) {
      color_pixel(i, j, *map);
      map++;
    }
  }
  return 0;
}*/

int set_mode_graphic(uint16_t mode) {

  //  VBE INT 0x10 Interface

  reg86_t r;

  memset(&r, 0, sizeof(reg86_t));

  r.ax = SET_VBE_MODE;   // VBE call, function 02 -- set VBE mode
  r.bx = 1 << 14 | mode; // set bit 14: linear framebuffer
  r.intno = VIDEO_CARD_BIOS;
  if (sys_int86(&r) != OK) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }

  return 0;
}

int map_vram(uint16_t mode) {

  struct minix_mem_range mr;
  unsigned int vram_base; 
  unsigned int vram_size; 
  int r;



  if (vbe_get_mode_info(mode, &vmi_p) != 0) {
    printf("vbe_get_mode_info failed\n");
    return 1;
  }

  //set vram_base and size
  vram_base = vmi_p.PhysBasePtr;

  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bytes_per_pixel = (vmi_p.BitsPerPixel) / 8;

  vram_size = h_res * v_res * bytes_per_pixel;



  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }

 

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    panic("couldn't map video memory");
    return 1;
  }

  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

  //desenhar linha horizontal , incrementar o x e preencher o pixel com aquelas coordenadas

  for (int i = 0; i < len; i++) {
    if (color_pixel(x + i, y, color) != 0) {
      printf("[ERROR] Could not fill the pixel with color\n");
      return 1;
    }
  }

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y,
                   uint16_t width, uint16_t height, uint32_t color) {

  //chamar vg-draw_hline at� que y == height

  for (int j = 0; j < height; j++) {
    if (vg_draw_hline(x, y + j, width, color) != 0) {
      printf("[ERROR] Could not  draw the horizontal line\n");
      return 1;
    }
  }

  return 0;
}

int color_pixel(uint16_t x, uint16_t y, uint32_t color) {

  uint8_t *pointer;

  if (x < 0 || x > h_res) {
    printf("[ERROR] X out of index \n");
    return 1;
  }

  if (y < 0 || y > v_res) {
    printf("[ERROR] Y out of index \n");
    return 1;
  }

  pointer = (unsigned char *) video_mem;

  uint8_t auxiliar;

  for (int k = 0; k < bytes_per_pixel; k++) {
    auxiliar = color & AUX_COLOR;

    *(pointer + (y * h_res * bytes_per_pixel) + (x * bytes_per_pixel) + k) = auxiliar;

    get_next_byte(&color);
  }

  return 0;
}

void get_next_byte(uint32_t *var) {
  *(var) = *(var) >> 8;
}

void get_rect_dimensions(uint8_t nr, uint16_t *width, uint16_t *height) {
  *width = h_res / nr;
  *height = v_res / nr;
  return;
}

uint32_t index_mode(uint8_t row, uint8_t col, uint8_t no_rectangles, uint8_t step, uint32_t first) {
  return (first + (row * no_rectangles + col) * step) % (1 << vmi_p.BitsPerPixel);
}


uint32_t get_color_direct(uint8_t row, uint8_t col, uint8_t step,uint32_t first) { 
  uint32_t r1, g1, b1,red,blue,green;
  r1 = (first >> vmi_p.RedFieldPosition) % (1 << vmi_p.RedMaskSize);
  g1 = (first >> vmi_p.GreenFieldPosition) % (1 << vmi_p.GreenMaskSize);
  b1 = (first >> vmi_p.BlueFieldPosition) % (1 << vmi_p.BlueMaskSize);

  red = (r1 + col * step) % (1 << vmi_p.RedMaskSize);
  green = (g1 + row * step) % (1 << vmi_p.GreenMaskSize);
  blue = (b1 + (col + row) * step) % (1 << vmi_p.BlueMaskSize);

  return (red << vmi_p.RedFieldPosition | green << vmi_p.GreenFieldPosition | blue);
}

int print_xpm(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t img;
  uint8_t *base;

  base = xpm_load(xpm, XPM_INDEXED, &img);
  if (base == NULL) {
    printf("couldnt read xpm map!\n");
    return 1;
  }

  pixwidth=img.width;
  pixheight = img.height;

  for (uint16_t j = y; j < y + pixheight; j++) { 
    for (uint16_t i = x; i < x + pixwidth; i++){
      color_pixel(i, j, *(base));
      base++;
    }
  }
  return 0;
}

uint16_t getpixwidth() { return pixwidth; }

uint16_t getpixheight() { return pixheight; }

int getnext(uint16_t *xi, uint16_t *yi, uint16_t xf, uint16_t yf, int16_t speed, uint16_t counter) {
  if (speed >= 0) {
    if (*xi != xf) {
      if (*xi < xf) {
        (*xi) += speed;
      }
      else {
        (*xi) -= speed;
      }
    }
    if (*yi != yf) {
      if (*yi < yf) {
        (*yi) += speed;
      }
      else {
        (*yi) -= speed;
      }
    }
  }
  else {
    if (counter % (-speed) == 0) {
      if (*xi != xf) {
        if (*xi < xf) {
          (*xi)++;
        }
        else {
          (*xi)--;
        }
      }
      if (*yi != yf) {
        if (*yi < yf) {
          (*yi)++;
        }
        else {
          (*yi)--;
        }
      }
    }
  }
  if ((*xi > xf) || (*yi > yf)) {
    *xi = xf;
    *yi = yf;
    return 0;
  }
  return 0;
}

int gethres() { return h_res; }

int getvres() { return v_res; }

