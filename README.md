# ft_ping

Simple remake of Ping based on the Debian "inetutils" version.

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
This project is dependent on my [libft](https://github.com/kixikCodes/libft).
You can use Make to compile, ideally in Debian version 7 or higher (as per the subject).
