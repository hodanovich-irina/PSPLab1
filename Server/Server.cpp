#include "ServerTCP.h"

int main()
{
	int clientCount = 0;
	std::string input;
	std::string a;
	std::string b;

	do
	{
		std::cout << "Enter clients count:" << std::endl;
		std::cin >> input;
	} while (input[0] < '0' || input[0] > '9');

	clientCount = stoi(input);

	Server server(1000, clientCount);

	do
	{
		std::cout << "Enter A:" << std::endl;
		std::cin >> a;
	} while (a[0] == '-');

	do
	{
		std::cout << "Enter B:" << std::endl;
		std::cin >> b;
	} while (b[0] == '-');

	std::thread* threads = server.listenClients(stoi(a), stoi(b));

	while (server.clientFinished != clientCount);

	std::cout << "Square: " << server.get_square() << std::endl;

	int tmp = getchar();

	return 0;
}
