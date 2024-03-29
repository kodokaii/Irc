NAME 		= ircserv

CXX			= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98 -I.
LDLIBS		=

KDO			= kdolib
KDOLIB		= $(KDO)/kdolib.a

SRC 		= Config.cpp\
			  IrcClient.cpp\
			  IrcMessage.cpp\
			  IrcServer.cpp\
			  IrcChannel.cpp\
			  main.cpp\
			  lusers.cpp\
			  motd.cpp

			  # lusers and motd fucking required because
			  # of recursive references whatever

OBJ 		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(KDOLIB) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(KDOLIB) $(LDLIBS)

$(KDOLIB): $(KDO)
	$(MAKE) -C $(KDO)

$(KDO):
	$(CLONE) https://github.com/kodokaii/kdolib_cpp.git $(KDO)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if [ -d "$(KDO)" ]; then $(MAKE) clean -C $(KDO); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(KDOLIB)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(KDO)

re: fclean fast

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all clean fclean clear re
