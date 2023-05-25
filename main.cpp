#include <SDKDDKVer.h>

#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
//-------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

struct lol {
    boost::asio::deadline_timer timer;

    int cnt = 0;

    boost::chrono::system_clock::time_point start;

    lol(boost::asio::io_context &io_context) : timer(io_context), start(boost::chrono::system_clock::now()) {
        timer.expires_from_now(boost::posix_time::milliseconds(1));
        timer.async_wait(boost::bind(&lol::foo, this));
    }

    void foo() {
        cnt++;
        if (cnt % 100 == 0) {
            boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
            std::cout << sec.count() << "s " << cnt << std::endl;
        }

        // переставляем таймер для следующего вызова foo()
        timer.expires_from_now(boost::posix_time::milliseconds(1));
        //timer.expires_at(timer.expires_at() + boost::posix_time::milliseconds(1));

        /*
        expires_from_now
        1.68849s 100
        3.22438s 200
        4.7731s 300
        6.3635s 400
        7.95451s 500
        9.54278s 600
        10.9797s 700
        12.5522s 800
        14.0614s 900
        15.8326s 1000
        */

        /*
        expires_at
        0.104429s 100
        0.205069s 200
        0.304973s 300
        0.400157s 400
        0.511599s 500
        0.606286s 600
        0.70955s 700
        0.805118s 800
        0.901121s 900
        1.0109s 1000
         */

        timer.async_wait(boost::bind(&lol::foo, this));
    }
};

int main() {
    boost::asio::io_context io_context;
    lol loller(io_context);

    io_context.run();
}
