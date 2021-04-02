%{
char text[1000];
int copy = 1;
int brackets = 0;
int error = 0;
%}

%%

[*][*][^\n]*[\n] { if(brackets == 0) strcat(text, "\n"); }
["][^"]*["]  { if(copy == 1)
                    strcat(text, yytext); }
[{]       { copy = 0; brackets++; }
[}]       { if(brackets <= 0) brackets = -1;
            if(brackets <= 0) copy = 0;
            if(brackets > 0) copy = 1;
            if(brackets > 0) brackets = 0; }
\n        { if(copy == 1)
              strcat(text, "\n"); }
.         { if(copy == 1)
              strcat(text, yytext);
            else ; }

%%

int main() {
    yylex();
    printf("%s", text);
    if (brackets != 0) {
      printf("syntax error\n");
    }
    return 0;
}
