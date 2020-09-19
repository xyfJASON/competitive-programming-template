std::default_random_engine generator;

int a = std::uniform_int_distribution<int> (0,9)(generator); // [0, 9]
int b = std::uniform_int_distribution<int> (1, 100)(generator); // [1, 100]