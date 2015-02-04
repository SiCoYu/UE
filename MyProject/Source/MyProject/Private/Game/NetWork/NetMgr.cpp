#include "MyProject.h"
#include "NetMgr.h"

//NetMgr::NetMgr(StdLog *p)
//	: SocketHandler(p), m_done(false), m_quit(false) 
//{
//
//}
//NetMgr::~NetMgr() 
//{
//
//}
//
//void NetMgr::List(TcpSocket *p) 
//{
//	for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++)
//	{
//		Socket *p0 = (*it).second;
//#ifdef ENABLE_POOL
//		if (dynamic_cast<ISocketHandler::PoolSocket *>(p0))
//		{
//			p->Send("PoolSocket\n");
//		}
//		else
//#endif
//			if (dynamic_cast<HttpGetSocket *>(p0))
//			{
//				p->Send("HttpGetSocket\n");
//			}
//			else
//				if (dynamic_cast<TcpSocket *>(p0))
//				{
//					p->Send("TcpSocket\n");
//				}
//				else
//				{
//					p->Send("Some kind of Socket\n");
//				}
//	}
//}
//void NetMgr::SetQuit() 
//{ 
//	m_quit = true; 
//}
//
//bool NetMgr::Quit() 
//{ 
//	return m_quit; 
//}
//
//void NetMgr::CheckHtml() 
//{
//	if (m_done)
//	{
//		if (m_ok)
//			printf("Html OK:\n%s\n", m_html.c_str());
//		else
//			printf("Html Failed\n");
//		m_done = false;
//	}
//}

//int main()
//{
//	try
//	{
//		StdoutLog log;
//		MyHandler h(&log);
//
//#ifdef ENABLE_RESOLVER
//		h.EnableResolver(9999);
//#endif
//		//	Utility::ResolveLocal();
//		printf(" *** My hostname: %s\n", Utility::GetLocalHostname().c_str());
//		printf(" *** My local IP: %s\n", Utility::GetLocalAddress().c_str());
//
//		// socks4 options
//		/*
//		h.SetSocks4Host("127.0.0.1");
//		h.SetSocks4Port(1080);
//		h.SetSocks4Userid("www.alhem.net");
//		h.SetSocks4TryDirect( true );
//		printf("Socks4Host: %x\n", h.GetSocks4Host());
//		*/
//
//		// first server
//		ListenSocket<MySocket> l1(h);
//		if (l1.Bind(1024))
//		{
//			printf("Bind 1024 failed\n");
//			exit(-1);
//		}
//		h.Add(&l1);
//
//		// second server
//		ListenSocket<MySocket> l2(h);
//		if (l2.Bind(1025))
//		{
//			printf("Bind 1025 failed\n");
//			exit(-1);
//		}
//		h.Add(&l2);
//
//		// line server
//		ListenSocket<OrderSocket> l3(h);
//		if (l3.Bind(1027))
//		{
//			printf("Bind 1027 failed\n");
//			exit(-1);
//		}
//		h.Add(&l3);
//
//		// http debug
//		ListenSocket<HttpDebugSocket> l4(h);
//		if (l4.Bind(8080))
//		{
//			printf("Bind 8080 failed\n");
//			exit(-1);
//		}
//		h.Add(&l4);
//
//		// wait for resolver to really start
//#ifdef ENABLE_RESOLVER
//		printf("Waiting for resolver ...");
//		while (!h.ResolverReady())
//			;
//		printf(" resolver ready!\n");
//#endif
//
//		TestSocket ts(h);
//		printf(">>> TestSocket.Open\n");
//		ts.Open("localhost", 1027);
//		printf(">>> Adding TestSocket\n");
//		h.Add(&ts);
//
//		printf(">>> Enter mainloop\n");
//		h.Select(0, 0);
//		while (!h.Quit())
//		{
//			h.Select(1, 0);
//		}
//		printf(">>> Leaving mainloop\n");
//
//		return 0;
//	}
//	catch (const Exception& e)
//	{
//		std::cerr << e.ToString() << std::endl;
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << e.what() << std::endl;
//	}
//}
