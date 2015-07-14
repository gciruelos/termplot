#include "parser.h"

void assign(struct op_s * op, char opch){
  int i;
  for(i = 0; i<OPS_SIZE; i++){
    if(ops[i].op == opch){
      *op = ops[i];
    }
  }
  // op? op, op. op op op op. op!
}


unsigned int next_token(const char *expr, token * res){

  unsigned int i = 0;
  switch(*expr){
    case '\0': res->type = ERR; break;
    case '+': 
    case '-': 
    case '*': 
    case '/': 
              res->type = OP; assign(&(res->data.op), *expr); i++; break;
    case '(': res->type = PARL; i++; break;
    case ')': res->type = PARR; i++; break;
    case 'x': res->type = VAR; i++; break;
    default: 
              res->type = NUM;
              res->data.i = 0;
              while(isdigit(expr[i])){
                res->data.i *= 10;
                res->data.i += (int) (expr[i]) - (int) '0';

                i++;
              } 
              break;
  }
  return i;
}

void prnt_token(token tok){
  if(tok.type == NUM){
    printf("{NUM %d}", tok.data.i);
  } else if(tok.type == OP){
    printf("{OP %c}", tok.data.op.op);
  } else if(tok.type == VAR){
    printf("{VAR X}");
  }else{
    printf("{WHAT %d}", tok.type);
  }
  //printf("\n");
}


void print_caca(token ** s, int sz){
 int j;
 for(j = 0; j<sz; j++){
   printf("#");prnt_token(*s[j]);
 }
 printf("\n");
}

expr parse(const char * in){ 

  token ** queue = (token **) malloc(sizeof(token)*100); int queue_last = -1;
  token * stack[100]; int stack_top = -1;


  token * last_tok = NULL;

  int forward;

  while(*in != '\0'){

   
    token * tok = malloc(sizeof(token));
  
    forward = next_token(in, tok);
    in += forward;


    //chequear si es - unario o binario 
    if(tok->type == OP && tok->data.op.op == '-'){
      if(last_tok == NULL || last_tok->type == PARL || last_tok->type == OP){
        assign(&(tok->data.op), '_');
      }
    }
    
    if(tok->type == NUM || tok->type == VAR){
      queue[++queue_last] = tok;
    } else if(0){ //function token
    } else if(0){ //function argument separator
    } else if(tok->type == OP){
      struct op_s o1 = tok->data.op;
    
      while(stack_top >= 0 && stack[stack_top]->type == OP){
        struct op_s o2 = stack[stack_top]->data.op;
        if((o1.assoc == ASSOC_LEFT && o1.prec <= o2.prec) ||
           (o1.assoc == ASSOC_RIGHT && o1.prec < o2.prec)){
          queue[++queue_last] = stack[stack_top--];
        } else break;
      }
      stack[++stack_top] = tok;
    } else if(tok->type == PARL){
      stack[++stack_top] = tok;
    } else if(tok->type == PARR){
      while(stack[stack_top]->type != PARL){
        queue[++queue_last] = stack[stack_top--];
      }
      if(stack[stack_top]->type == PARL){
        free(stack[stack_top]);
        stack_top--;
      }
    }

    last_tok = tok;
  }

  while(stack_top >= 0){
    queue[++queue_last] = stack[stack_top--];
  }

 expr res;
 res.parsed = queue;
 res.size = queue_last+1;
 return res;


}

double eval(expr e, double x){
  double stack[100]; int stack_top = -1;

  int i;
  for(i = 0; i<e.size; i++){
    token * t = e.parsed[i];
    if (t->type == NUM){
      stack[++stack_top] = (double) t->data.i;
    } else if(t->type == VAR){
      stack[++stack_top] = x;
    } else if(t->type == OP){
      struct op_s o = t->data.op;
      printf("%c\n", o.op);
      if(o.unary){
        
        stack[stack_top] = o.function.un(stack[stack_top]);
      } else{
        double a1 = stack[stack_top-1];
        double a2 = stack[stack_top];
        
        stack[--stack_top] = o.function.bin(a1, a2);
      }
    }
  }

  return stack[0];

}

void delete_expr(expr d){
  int i;
  for(i = 0; i<d.size; i++){
    free(d.parsed[i]);
  }
  free(d.parsed);
}
/*
int main(){
  char e[] = "x*x";
  expr a = parse(e);
  print_caca(a.parsed, a.size);
  printf("%f\n", eval(a, 1.2));
  return 0;
  delete_expr(a);
}
*/
