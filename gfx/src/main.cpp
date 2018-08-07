#include "Window.hpp"
#include "Map.hpp"

#include "Time.hpp"
#include "CoreInclude.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int client_socket(char *ip, uint16_t port)
{
	struct sockaddr_in	client_addr;
	int					        sockfd;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		return (-1);

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	if ((client_addr.sin_addr.s_addr = inet_addr(ip)) == (in_addr_t)-1)
		return (-1);
	if (connect(sockfd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in)) == -1)
	{
		printf("No bueno %s\n", strerror(errno));		
		return (-1);
	}
	return (sockfd);
}

int	main(int argc, char *argv[])
{
	int	clientfd;
		
	if (argc <= 2
	    || ((clientfd = client_socket(argv[1], atoi(argv[2]))) == -1))
		return (EXIT_FAILURE);
	
	Window window(1600, 900, "mappy");
	Map map(clientfd);
	Time timer;
	
	char buf[10];
	read(clientfd, buf, 10);
	write(clientfd, "GRAPHIC\n", 8);

	glClearColor(0.133, 0.133, 0.133, 1);
	while (!window.ShouldClose())
	{
		timer.Step();
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		window.Clear();

		map.Update(timer.Delta(), window);
		
		window.Render();
	}	
	window.Close();
}
