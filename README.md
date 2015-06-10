Project design
-------
0. Use only one thread for all requests (quotes reading, handling tcp connection, parsing client requests). All operations are done in async way, so that thread is not blocked. Use boost asio for async operations.
0. When user connects to oms, server assigns account name to him.
0. ports, ticker name and quotes file name are configurable. Please find confiuration file src/config/config.json
0. I have a few assumptions for the Brownian Motion, matching algorithm, order book keeping, tick size, etc. Please find the details in the report.


Usage
-------

0. for a new terminal session, setup session envrionment by running : 
```
source ./env.sh
```

1. build all and run unit test
```
make all
```

2. you may build each individually
```
make serve
make listen
make connect
make unit_test
```

0. generate quote
```
./generate
```

0. start exchange server
```
./serve
```

0. listen quotes updates
```
./listen markets # output in json format
./listen markets --current # output in table format, refresh on new quote received
```

0. listen order updates from <account-name>. If you put server as account-name, you will listen all order updates from server
```
./listen orders <account-name>
```

0. listen trade updates from account-name. If you put server as account-name, you will listen all trade updates from server
```
./listen trades <account-name>
```

0. connect to exchange server, you will be assigned an account-name. Submit new order by typing in format, for example

```
./connect oms
buy 1234 5@100
sell 1234 5@100
```

TODO:
=============
0. Design better client/server communication messages and protocol
0. Use protobuf message for communication
0. Use multi-threading hanlding large amount of user
0. Support multiple ticker quotes
0. Separate more modules to achieve better testability