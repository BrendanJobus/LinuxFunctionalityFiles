%{
int yorno = 0;
%}

%%

[a-z][A-Z]$	{yorno = 1;}
.			;

%%

int main()
{
    yylex();
    printf("%8d\n", yorno);
    return 0;
}
