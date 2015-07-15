#include "ui_curses.h"

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


void set_terminal_size(){
  getmaxyx(stdscr,options.height,options.width);
}
    

void wshowchc(int y, int x, int color, char ch){
  attron(COLOR_PAIR(color)); 
  mvaddch(y, x, ch);
  attroff(COLOR_PAIR(color));
}


void show_function_list(int index, int color, char * str){
  mvprintw(1+index, 0, "%d", index); 
  attron(COLOR_PAIR(color));
  mvprintw(1+index, 2,"f(x) = %s", str); 
  attroff(COLOR_PAIR(color));
}

void end_curses() {
  if (curses_started && !isendwin())
    delwin(win);
    endwin();
    refresh();
}

void start_curses() {
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
    atexit(end_curses);
    curses_started = true;
    }


  int i, j;
  for(i = 0; i<16; i++){
     for(j = 0; j<16; j++){
       init_pair(j*16 + i, i, j); // bg*16 + fg
     }
  }
}

void input_command(){
  int ch;
  int i = 0;
  int height = options.height;
  mvprintw(height-1, 0, ":");

  char command[500]; 

  while((ch = getch()) != 10){
    if(ch == 127){
      i--;
      mvprintw(height-1, i+1, " ");
      mvprintw(height-1, i+1, "");
    } else{
      mvprintw(height-1, i+1, "%c", ch);
      command[i] = ch;
      i++;
    }
  }
  command[i] = '\0';
  fprintf(stderr, "hola");
  run_command(command);
}


int input(){
  static double zoom_factor = 0.1;

  int ch = getch();
  switch(ch){
    case ERR: return -2;
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



void draw_axis(){

  int height = options.height;
  int width = options.width;

  int y, x;
  int x_0 = width/2  - options.x_center/options.x_zoom;
  int y_0 = height/2 + options.y_center/options.y_zoom;
  
  for(y = 0; y<height; y++){
    mvprintw(y, x_0, "|");
  }
   
  for(x = 0; x<width; x++){
   mvprintw(y_0, x, "-");
  }
  //mvprintw(y_0, x_0, "+");

  for(x = 0; x<width; x+=10){ 
   mvprintw(y_0+1, x, "%.3f", options.x_center + options.x_zoom * (x - width/2));
  }

  for(y = 0; y<height; y+=3){ 
   mvprintw(y, x_0+1, " %.3f", options.y_center + options.y_zoom * (height/2-y));
  }

}


