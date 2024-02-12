#include "aoclient.h"

#include "area_data.h"
#include "config_manager.h"
#include "packet/packet_factory.h"
#include "server.h"

// This file is for functions used by various commands, defined in the command helper function category in aoclient.h
// Be sure to register the command in the header before adding it here!

void AOClient::cmdDefault(int argc, QStringList argv)
{
  Q_UNUSED(argc);
  Q_UNUSED(argv);

  sendServerMessage("Invalid command.");
  return;
}

QStringList AOClient::buildAreaList(int area_idx)
{
  QStringList entries;
  QString area_name = server->getAreaName(area_idx);
  AreaData *area = server->getAreaById(area_idx);
  entries.append("=== " + area_name + " ===");
  switch (area->lockStatus())
  {
  case AreaData::LockStatus::LOCKED:
    entries.append("[LOCKED]");
    break;
  case AreaData::LockStatus::SPECTATABLE:
    entries.append("[SPECTATABLE]");
    break;
  case AreaData::LockStatus::FREE:
  default:
    break;
  }
  entries.append("[" + QString::number(area->playerCount()) + " users][" + QVariant::fromValue(area->status()).toString().replace("_", "-") + "]");
  const QVector<AOClient *> l_clients = server->getClients();
  for (AOClient *l_client : l_clients)
  {
    if (l_client->m_current_area == area_idx && l_client->hasJoined())
    {
      QString char_entry = "[" + QString::number(l_client->m_id) + "] " + l_client->m_current_char;
      if (l_client->m_current_char == "")
      {
        char_entry += "Spectator";
      }
      if (l_client->m_showname != "")
      {
        char_entry += " (" + l_client->m_showname + ")";
      }
      if (area->owners().contains(l_client->m_id))
      {
        char_entry.insert(0, "[CM] ");
      }
      if (m_authenticated)
      {
        char_entry += " (" + l_client->getIpid() + "): " + l_client->m_ooc_name;
      }
      if (l_client->m_is_afk)
      {
        char_entry += " [AFK]";
      }
      entries.append(char_entry);
    }
  }
  return entries;
}

int AOClient::genRand(int min, int max)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
  qsrand(QDateTime::currentMSecsSinceEpoch());
  quint32 random_number = (qrand() % (max - min + 1)) + min;
  return random_number;

#else
  return QRandomGenerator::system()->bounded(min, max + 1);
#endif
}

void AOClient::diceThrower(int sides, int dice, bool p_roll, int roll_modifier)
{
  if (sides < 0 || dice < 0 || sides > ConfigManager::diceMaxValue() || dice > ConfigManager::diceMaxDice())
  {
    sendServerMessage("Dice or side number out of bounds.");
    return;
  }
  QStringList results;
  for (int i = 1; i <= dice; i++)
  {
    results.append(QString::number(AOClient::genRand(1, sides) + roll_modifier));
  }
  QString total_results = results.join(" ");
  if (p_roll)
  {
    if (roll_modifier)
    {
      sendServerMessage("You rolled a " + QString::number(dice) + "d" + QString::number(sides) + "+" + QString::number(roll_modifier) + ". Results: " + total_results);
    }
    else
    {
      sendServerMessage("You rolled a " + QString::number(dice) + "d" + QString::number(sides) + ". Results: " + total_results);
    }
    return;
  }
  if (roll_modifier)
  {
    sendServerMessageArea(m_ooc_name + " rolled a " + QString::number(dice) + "d" + QString::number(sides) + "+" + QString::number(roll_modifier) + ". Results: " + total_results);
  }
  else
  {
    sendServerMessageArea(m_ooc_name + " rolled a " + QString::number(dice) + "d" + QString::number(sides) + ". Results: " + total_results);
  }
}

QString AOClient::getAreaTimer(int area_idx, int timer_idx)
{
  AreaData *l_area = server->getAreaById(area_idx);
  QTimer *l_timer;
  QString l_timer_name = (timer_idx == 0) ? "Global timer" : "Timer " + QString::number(timer_idx);

  if (timer_idx == 0)
  {
    l_timer = server->timer;
  }
  else if (timer_idx > 0 && timer_idx <= 4)
  {
    l_timer = l_area->timers().at(timer_idx - 1);
  }
  else
  {
    return "Invalid timer ID.";
  }

  if (l_timer->isActive())
  {
    QTime l_current_time = QTime(0, 0).addMSecs(l_timer->remainingTime());

    return l_timer_name + " is at " + l_current_time.toString("hh:mm:ss.zzz");
  }
  else
  {
    return l_timer_name + " is inactive.";
  }
}

long long AOClient::parseTime(QString input)
{
  QRegularExpression l_regex("(?:(?:(?<year>.*?)y)*(?:(?<week>.*?)w)*(?:(?<day>.*?)d)*(?:(?<hr>.*?)h)*(?:(?<min>.*?)m)*(?:(?<sec>.*?)s)*)");
  QRegularExpressionMatch match = l_regex.match(input);
  QString str_year, str_week, str_hour, str_day, str_minute, str_second;
  int year, week, day, hour, minute, second;

  str_year = match.captured("year");
  str_week = match.captured("week");
  str_day = match.captured("day");
  str_hour = match.captured("hr");
  str_minute = match.captured("min");
  str_second = match.captured("sec");

  bool l_is_well_formed = false;
  QString concat_str(str_year + str_week + str_day + str_hour + str_minute + str_second);
  concat_str.toInt(&l_is_well_formed);

  if (!l_is_well_formed)
  {
    return -1;
  }

  year = str_year.toInt();
  week = str_week.toInt();
  day = str_day.toInt();
  hour = str_hour.toInt();
  minute = str_minute.toInt();
  second = str_second.toInt();

  long long l_total = 0;
  l_total += 31622400 * year;
  l_total += 604800 * week;
  l_total += 86400 * day;
  l_total += 3600 * hour;
  l_total += 60 * minute;
  l_total += second;

  if (l_total < 0)
  {
    return -1;
  }

  return l_total;
}

QString AOClient::getReprimand(bool f_positive)
{
  if (f_positive)
  {
    return ConfigManager::praiseList().at(genRand(0, ConfigManager::praiseList().size() - 1));
  }
  else
  {
    return ConfigManager::reprimandsList().at(genRand(0, ConfigManager::reprimandsList().size() - 1));
  }
}

bool AOClient::checkPasswordRequirements(QString f_username, QString f_password)
{
  QString l_decoded_password = decodeMessage(f_password);
  if (!ConfigManager::passwordRequirements())
  {
    return true;
  }

  if (ConfigManager::passwordMinLength() > l_decoded_password.length())
  {
    return false;
  }

  if (ConfigManager::passwordMaxLength() < l_decoded_password.length() && ConfigManager::passwordMaxLength() != 0)
  {
    return false;
  }

  else if (ConfigManager::passwordRequireMixCase())
  {
    if (l_decoded_password.toLower() == l_decoded_password)
    {
      return false;
    }
    if (l_decoded_password.toUpper() == l_decoded_password)
    {
      return false;
    }
  }
  else if (ConfigManager::passwordRequireNumbers())
  {
    QRegularExpression regex("[0123456789]");
    QRegularExpressionMatch match = regex.match(l_decoded_password);
    if (!match.hasMatch())
    {
      return false;
    }
  }
  else if (ConfigManager::passwordRequireSpecialCharacters())
  {
    QRegularExpression regex("[~!@#$%^&*_-+=`|\\(){}\[]:;\"'<>,.?/]");
    QRegularExpressionMatch match = regex.match(l_decoded_password);
    if (!match.hasMatch())
    {
      return false;
    }
  }
  else if (!ConfigManager::passwordCanContainUsername())
  {
    if (l_decoded_password.contains(f_username))
    {
      return false;
    }
  }
  return true;
}

void AOClient::sendNotice(QString f_notice, bool f_global)
{
  QString l_message = "A moderator sent this ";
  if (f_global)
  {
    l_message += "server-wide ";
  }
  l_message += "notice:\n\n" + f_notice;
  sendServerMessageArea(l_message);
  ServerAOPacket *l_packet = PacketFactory::createPacket("BB", {l_message});
  if (f_global)
  {
    server->broadcast(l_packet);
  }
  else
  {
    server->broadcast(l_packet, m_current_area);
  }
}
