#pragma once

#include "server_global.h"

#include <QObject>
#include <QtNetwork>

/**
 * @brief Represents the advertiser of the server. Sends current server information to masterserver.
 */
class ECHO_SERVER_EXPORT Advertiser : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Constructor for the HTTP_Advertiser class.
   */
  explicit Advertiser();

  /**
   *  @brief Deconstructor for the HTTP_Advertiser class. Yes, that's it. Can't say more about it.
   */
  ~Advertiser();

public slots:

  /**
   * @brief Establishes a connection with masterserver to register or update the listing on the masterserver.
   */
  void msAdvertiseServer();

  /**
   * @brief Reads the information send as a reply for further error handling.
   * @param reply Response data from the masterserver. Information contained is send to the console if debug is enabled.
   */
  void msRequestFinished(QNetworkReply *f_reply);

  /**
   * @brief Updates the playercount of the server in the advertiser.
   */
  void updatePlayerCount(int f_current_players);

  /**
   * @brief Updates advertisement values
   */
  void updateAdvertiserSettings();

private:
  /**
   * @brief Pointer to the network manager, necessary to execute POST requests to the masterserver.
   */
  QNetworkAccessManager *m_manager;

  /**
   * @brief Name of the server send to the masterserver. Changing this will change the display name in the serverlist
   */
  QString m_name;

  /**
   * @brief Optional hostname of the server. Can either be an IP or a DNS name. Disabled automatic IP detection of ms3.
   */
  QString m_hostname;

  /**
   * @brief Description of the server that is displayed in the client when the server is selected.
   */
  QString m_description;

  /**
   * @brief Client port for the AO2-Client.
   */
  int m_port;

  /**
   * @brief Websocket proxy port for WebAO users.
   */
  int m_ws_port;

  /**
   * @brief Maximum amount of clients that can be connected to the server.
   */
  int m_players;

  /**
   * @brief URL of the masterserver that m_manager posts to. This is almost never changed.
   */
  QUrl m_masterserver;

  /**
   * @brief Controls if network replies are printed to console. Should only be true if issues communicating with masterserver appear.
   */
  bool m_debug;
};
