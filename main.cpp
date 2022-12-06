#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost::asio;
size_t read_complete(char * buf, const boost::system::error_code & err, size_t bytes)
{
    if ( err)
        return 0;
    bool found = std::find(buf, buf + bytes, -1) < buf + bytes;
    return not found;
}

int main() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::socket sock(service);
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8005));
    acceptor.accept(sock);
    std::cout << "новое подключение\n";
    while (true) {
        boost::asio::streambuf buff;
        std::string command;
        std::getline(std::cin,command);
        command+="\n";
        sock.write_some(boost::asio::buffer(command));
        //read(sock, boost::asio::buffer(command), boost::bind(read_complete,command,_1,_2));
        boost::asio::read_until(sock,buff,-1);
        std::cout << command;
    }
}
