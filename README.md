# Network-Practice
Following Jpres's Networking Tutorials

https://www.youtube.com/playlist?list=PLcacUGyBsOIBn5_vRWZF1qA_85qKJ6kTm

## Build

Release/x64로 빌드

정적 라이브러리로 빌드됨

사용할 프로젝트에서 PNet의 헤더파일들을 참조해야함

IncludeMe.h를 사용할 프로젝트에서 Include

PNet.lib를 사용할 프로젝트에서 링킹

## How to use

```
Process가 시작할 때 Network::Initialize()
Process가 끝날 때 Network::Shutdown()
```

connection.pm_outgoing에 Append()를 하면 연결된 상대에게 패킷을 Send함

### Server Side

1. Server 클래스를 상속 받아 아래 3개의 메서드를 override하여 사용
```
virtual void OnConnect(TCPConnection& newConnection);
virtual void OnDisconnect(TCPConnection& lostConnection, std::string reason);
virtual bool ProcessPacket(std::shared_ptr<Packet> packet);
```

2. Server 진행 순서
```
PNet::Server::Initialize()
PNet::Server::Frame()을 반복실행하여 Connection 대기와 Packet Receive, Packet Send, Packet Processing 진행
```

### Client Side

1. Client 클래스를 상속 받아 아래 4개의 메서드를 override하여 사용
```
virtual void OnConnect();
virtual void OnConnectFail();
virtual void OnDisconnect(std::string reason);
virtual bool ProcessPacket(std::shared_ptr<Packet> packet);
```

2. Client 진행 순서
```
PNet::Client::Connect()
PNet::Client::IsConnected()가 성공하면 PNet::Client::Frame()을 반복실행하여 Packet Receive, Packet Send, Packet Processing 진행
```
