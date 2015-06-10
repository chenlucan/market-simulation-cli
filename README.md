# market-simulation-cli

for a new terminal session, setup session envrionment by running : 
  source ./env.sh

# build all and run unit test
make all

# you may build each individually
make serve
make listen
make connect
make unit_test

# start exchange server
./serve

# listen quotes updates
./listen markets
./listen markets --current

# listen order updates from account-name. If you put server as account-name, you will listen all order updates from server
./listen orders <account-name>

# listen trade updates from account-name. If you put server as account-name, you will listen all trade updates from server
./listen trades <account-name>

# connect to exchange server, you will be assigned an account-name
# submit new order by typing in format:
#  - buy 1234 5@100
#  - sell 1234 5@100
./connect oms
