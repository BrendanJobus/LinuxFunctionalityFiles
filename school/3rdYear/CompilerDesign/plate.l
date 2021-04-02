%{
char text[1000];
int currentYear = 21;
char data[17];
char tmp[3];
int year = 0;
int yearDiff = 0;
%}

NUMBER 	[0-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?

COUNTY 	C|CE|CN|CW|D|DL|G|KE|KK|KY|L|LD|LH|LM|LS|MH|MN|MO|OY|RN|SO|T|W|WH|WX|WW
YEAR	[0-9][0-9][1,2]

OLDCOUNTY C|CE|CN|CW|D|DL|G|KE|KK|KY|L|LD|LH|LK|LM|LS|MH|MN|MO|OY|RN|SO|TN|TS|W|WD|WH|WX|WW
OLDYEAR	[0-9][0-9]

OFFYEAR [1][3][1,2]

%%

{YEAR}-{COUNTY}-{NUMBER}		{ strcpy(data, yytext);
					  tmp[0] = data[0];
					  tmp[1] = data[1];
					  year = atoi(tmp);
					  sprintf(tmp, "%d\n", (currentYear - year));
					  strcat(text, tmp);
					  year = 0;
					  yearDiff = 0;
					}
{OLDYEAR}-{OLDCOUNTY}-{NUMBER}([[:SPACE:]]|\n)	{ strcpy(data, yytext);
					  tmp[0] = data[0];
					  tmp[1] = data[1];
					  year = atoi(tmp);
					  yearDiff = currentYear - year;
					  if(yearDiff < 0) {
						currentYear += 100;
						yearDiff = currentYear - year;
						currentYear -= 100;
					  }
						sprintf(tmp, "%d\n", (yearDiff));
						strcat(text, tmp);
						year = 0;
						yearDiff = 0;
					}
{OFFYEAR}-{OLDCOUNTY}-{NUMBER} 	{ strcat(text, "8\n"); }
[\n]					;
[[:SPACE:]]*			;
[^\n^[[:SPACE:]]]*[\n]			{ strcat(text, "INVALID\n"); }
.					;

%%

int main() {
	yylex();
	printf("%s", text);
	return 0;
}
