%{
int count = 0;
%}

%%

[0-9]*[02468][[:space:]]   { count++; }
[0-9]*[02468][ \n]+   { count++; }
\n              ;
.               ;

%%

int main()
{
    yylex();
    printf("%d\n", count);
    return 0;
}