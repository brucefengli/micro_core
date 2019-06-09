#include <test/test_io.h>


int test_io(int argc, char* argv[])
{
    //init group
    std::shared_ptr<nio_thread_pool> pool = std::make_shared<nio_thread_pool>();
    pool->init(1);

    pool->start();

    //init acceptor
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 9999);
    std::shared_ptr<tcp_acceptor> acceptor = std::make_shared<tcp_acceptor>(pool->get_ios(), endpoint);

    acceptor->group(pool, pool);
    acceptor->channel_initializer(std::make_shared<echo_initializer>(), std::make_shared<echo_initializer>());

    acceptor->init();

    //init connector
    std::shared_ptr < tcp_connector> connector = std::make_shared<tcp_connector>();
    
    connector->group(pool, pool);
    connector->connector_initializer(std::make_shared<echo_connector_initializer>());
    connector->channel_initializer(std::make_shared<echo_initializer>(), std::make_shared<echo_initializer>());

    connector->init();

    connector->connect(endpoint);

    while (true)
    {

    }
    
    return 0;
}