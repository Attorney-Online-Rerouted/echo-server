#pragma once

#include "network/serveraopacket.h"
#include "server_global.h"

#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>
#include <QWebSocket>

class ServerAOPacket;

class ECHO_SERVER_EXPORT NetworkSocket : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Constructor for the network socket class.
   * @param QTcpSocket for communication with external AO2-Client
   * @param Pointer to the server object.
   */
  NetworkSocket(QTcpSocket *f_socket, QObject *parent = nullptr);

  /**
   * @brief Constructor for the network socket class.
   * @param QWebSocket for communication with external AO2-Client or WebAO clients.
   * @param Pointer to the server object.
   */
  NetworkSocket(QWebSocket *f_socket, QObject *parent = nullptr);

  /**
   * @brief Default destructor for the NetworkSocket object.
   */
  ~NetworkSocket();

  /**
   * @brief Returns the Address of the remote socket.
   *
   * @return QHostAddress object of the socket.
   */
  QHostAddress peerAddress();

  /**
   * @brief Closes the socket by request of the child AOClient object or the server.
   */
  void close();

  /**
   * @brief Closes the socket by request of the child AOClient object or the server.
   *
   * @param The close code to the send to the client.
   */
  void close(QWebSocketProtocol::CloseCode f_code);

  /**
   * @brief Writes data to the network socket.
   *
   * @param Packet to be written to the socket.
   */
  void write(ServerAOPacket *f_packet);

signals:

  /**
   * @brief handlePacket
   * @param f_packet
   */
  void handlePacket(ServerAOPacket *f_packet);

  /**
   * @brief Emitted when the socket has been closed and the client is disconnected.
   */
  void clientDisconnected();

private slots:
  /**
   * @brief Handles the reading and processing of TCP stream data.
   *
   * @return Decoded ServerAOPacket to be processed by the child AOClient object.
   */
  void readData();

  /**
   * @brief Handles the processing of WebSocket data.
   *
   * @return Decoded ServerAOPacket to be processed by the child AOClient object.
   */
  void ws_readData(QString f_data);

private:
  enum SocketType
  {
    TCP,
    WS
  };

  /**
   * @brief Union holding either a TCP- or Websocket.
   */
  union
  {
    QTcpSocket *tcp;
    QWebSocket *ws;
  } m_client_socket;

  /**
   * @brief Remote IP of the client.
   *
   * @details In the case of the WebSocket we also check if this has been proxy forwarded.
   */
  QHostAddress m_socket_ip;

  /**
   * @brief Defines if the client is a Websocket or TCP client.
   */
  SocketType m_socket_type;

  /**
   * @brief Filled with part of a packet if said packet could not be read fully from the client's socket.
   *
   * @details Per AO2's network protocol, a packet is finished with the character `%`.
   *
   * @see #is_partial
   */
  QString m_partial_packet;

  /**
   * @brief True when the previous `readAll()` call from the client's socket returned an unfinished packet.
   *
   * @see #partial_packet
   */
  bool m_is_partial;
};
