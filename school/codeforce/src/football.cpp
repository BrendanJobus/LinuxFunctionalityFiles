#include <iostream>

using namespace std;

int main() {
	string playerString;
	cin >> playerString;
	int team1 = 0, team2 = 0, numberOfPlayers, currentPlayer = 0;
	bool dangerous = false;

	numberOfPlayers = playerString.size();
	char players[playerString.size() + 1];
	playerString.copy(players, playerString.size() + 1);

	while(currentPlayer < numberOfPlayers)
	{
		if(players[currentPlayer] == '0')
		{
			team1++;
			team2 = 0;
			if(team1 >= 7)
			{
				dangerous = true;
				cout << "YES\n";
				break;
			}
		}
		else
		{
			team2++;
			team1 = 0;
			if(team2 >= 7)
			{
				dangerous = true;
				cout << "YES\n";
				break;
			}
		}
			
		currentPlayer++;
	}

	if(dangerous == false)
		cout << "NO\n";
}