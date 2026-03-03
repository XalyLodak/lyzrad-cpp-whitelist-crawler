# Lyzrad CPP Whitelist Crawler

This project is a SQL crawler designed to add or remove players from the whitelist of a Minecraft server. It uses a MariaDB database to store player information and their whitelist status.

You can link it with your Website to allow players to request access to the server, and you can manage their requests through the database.

## How it works

It polls the database at regular intervals to check for any changes in the whitelist status of players. If a player is added to the whitelist, the crawler will execute the necessary commands to grant them access to the Minecraft server. Conversely, if a player is removed from the whitelist, the crawler will revoke their access.

Every 100ms, the crawler checks the database for any updates to the whitelist status of players, yes, it's a pretty bad idea (RCON use a state to minimize the requests to Minecraft Server). If a player is added to the whitelist, the crawler will execute the necessary commands to grant them access to the Minecraft server. Conversely, if a player is removed from the whitelist, the crawler will revoke their access.

## Security Warning

**Never point this program directly at a public server.**
All data (RCON password, commands) is sent unencrypted.
Always use an SSH tunnel or VPN between your machine and the server.
```bash
# Example SSH tunnel
autossh -M 0 -N -L 25575:localhost:25575 user@your-server
```

## Configuration

Not for the moment, you need to compile the code with your modifications to use your configuration, but in the future, I plan to add a configuration file to avoid this.

## Build

To build the project, you need to have a GNU C++ compiler installed.

To install the compiler and the necessary libraries, you can use the following command on Debian-based systems:

```bash
sudo apt install g++ libmysqlcppconn-dev
```

Then, you can compile the project using the following command:

```bash
make
```

And, you can build and package it in Debian format with :

```bash
make deb
```

## Usage

To run the crawler, simply execute the compiled binary:

```bash
lyzrad-rcon
```

## License

This project is licensed under the [GNU GPLv3 License](/LICENSE), it is a French Free Software, you can use it, modify it and distribute it as you wish, but you must keep the same license and give credit to the original author. See the LICENSE file for more details.

## Contributing

Contributions are welcome! If you have any ideas for improvements or bug fixes, please feel free to submit a pull request, open an issue on the GitLab repository or send me an email at this address : [quentinduteil@xalystudio.fr](mailto:quentinduteil@xalystudio.fr).