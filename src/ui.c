#include "ui.h"

/*  
 *  Terminal to Reals
 *  -----------------
 *
 *  x -> options.x_center + options.x_zoom * (x - width/2));
 *  y -> options.y_center + options.y_zoom * (height/2-y));
 *     
 *
 *  Reals to Terminal
 *  -----------------
 *  
 *  Inverses of the ones before
 *
 */

#define BUFFER_SIZE 500
#define MAX_LEN 300
struct buffer_entry{
  char * buf;
  int x;
  int y;
  unsigned int color;
} * print_buffer[BUFFER_SIZE];
unsigned int buffer_next;


void update_cmd(){
  curs_set(1);
  mvaddstr(options.height-1, 0, command);
  clrtoeol();
  move(options.height-1, cursor);
  refresh();
}




void wprintf(int y, int x, unsigned int color, char * fmt, ...){
  struct buffer_entry * b = print_buffer[buffer_next++];
  
  va_list args;
  va_start(args, fmt);
  vsprintf(b->buf, fmt, args);
  va_end(args);

  b->y = y;
  b->x = x;
  b->color = color;
}



int input(){
  static double zoom_factor = 0.1;

  int ch = w_getch();
  switch(ch){
    case ERR: 
      return -2;
    case 'q': return -1;
    case 'z':
    case '+':
      options.x_zoom -= options.x_zoom*zoom_factor;
      options.y_zoom -= options.y_zoom*zoom_factor;
      break;
    case 'x':
    case '-':
      options.x_zoom += options.x_zoom*zoom_factor/(1-zoom_factor);
      options.y_zoom += options.y_zoom*zoom_factor/(1-zoom_factor);
      break;
    case KEY_UP:
      options.y_center += options.y_zoom;
      break;
    case KEY_DOWN:
      options.y_center -= options.y_zoom;
      break;
    case KEY_RIGHT:
      options.x_center += options.x_zoom;
      break;
    case KEY_LEFT:
      options.x_center -= options.x_zoom;
      break;
    case ':':
      input_command();
      break;
  }

  return 0; // everyting went fine
}





void init_ui(){
  start_ui();
  int i, j;
  for(i = 0; i<16; i++){
     for(j = 0; j<16; j++){
       init_pair(j*16 + i, i, j); // bg*16 + fg
     }
  }

  for(i = 0; i<BUFFER_SIZE; i++){
    print_buffer[i] = malloc(sizeof(struct buffer_entry)); 
    print_buffer[i]->buf = calloc(MAX_LEN, sizeof(char));
  }

  buffer_next = 0; 
}


void clean_ui(){
  int i;

  for(i = 0; i<BUFFER_SIZE; i++){
    free(print_buffer[i]->buf);
    print_buffer[i]->buf = NULL;
    free(print_buffer[i]);
    print_buffer[i] = NULL;
  }
  end_ui();
}




/* INTERFACE FUNCTIONS */ 

void set_terminal_size(){
  getmaxyx(stdscr,options.height,options.width);
}

void update_ui(){
  int i;
  struct buffer_entry * b;


  curs_set(1);
  for(i = 0; i < buffer_next; i++){
    b = print_buffer[i];
    attron(COLOR_PAIR(b->color));
    mvaddstr(b->y, b->x, b->buf);
    attroff(COLOR_PAIR(b->color));
  }
  buffer_next = 0;
  curs_set(0);
  refresh();
}

int w_getch(){
  return getch();
}




/* CURSES FUNCTIONS */ 

void start_ui() {
  if (curses_started) {
    refresh();
  }
  else {  
    win = initscr();
    start_color(); 
    cbreak();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    atexit(end_ui);
    curses_started = true;
    }
}


void end_ui() {
 if (curses_started && !isendwin()){
    delwin(win);
    endwin();
    refresh();
  }
}


