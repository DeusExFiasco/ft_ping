# ft_ping

Simple remake of Ping based on the Debian "inetutils" version. Also note that Norminette does not apply to mastery projects, as far as I can tell. The `fflush` function is justified as a nacessary extra function to allow for the flood ping feature.

### Included Flags
- `-v`: verbose output, will print more information such as the socket info and the reverse DNS hostname
- `-q`: quiet output, will silence all ping logs regardless of other options. Other information still shown.
- `-f`: flood ping, will bombard the target with as many packets as possible and print a `.` per lost packet.
- `-t`: set your own TTL value for socket, must be a positive integer directly after the flag.
- `-?`: help menu, will print a usage guide and available options, then exit.

The options can be used in succession with eachother.
(**NOT** as a combined flag, e.g.: "`-vfq`".)
((_And obviously not the help option..._))

### Dependencies and Usage
This project is dependent on my [libft](https://github.com/DeusExFiasco/libft).
You can use Make to compile, ideally in Debian version 7 or higher (as per the subject).

To run inside a Docker container with Debian Trixie (latest stable, still allowed), do:

`make docker`

and the to enter it in interactive mode to run ft_ping do:

`docker run --rm -it --cap-add=NET_RAW ft_ping`

The purpose/reason of this container is that raw sockets require sudo rights to be used. Seeing as sudo is not available on campus computers, the evaulation must be done in either a VM or a container.
