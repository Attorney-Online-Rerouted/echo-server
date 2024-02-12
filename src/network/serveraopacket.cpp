#include "network/serveraopacket.h"

#include "packet/packet_askchaa.h"
#include "packet/packet_casea.h"
#include "packet/packet_cc.h"
#include "packet/packet_ch.h"
#include "packet/packet_ct.h"
#include "packet/packet_de.h"
#include "packet/packet_ee.h"
#include "packet/packet_factory.h"
#include "packet/packet_hi.h"
#include "packet/packet_hp.h"
#include "packet/packet_id.h"
#include "packet/packet_mc.h"
#include "packet/packet_ms.h"
#include "packet/packet_pe.h"
#include "packet/packet_pw.h"
#include "packet/packet_rc.h"
#include "packet/packet_rd.h"
#include "packet/packet_rm.h"
#include "packet/packet_rt.h"
#include "packet/packet_setcase.h"
#include "packet/packet_zz.h"

ServerAOPacket::ServerAOPacket(QStringList p_contents)
    : m_content(p_contents)
    , m_escaped(false)
{}

const QStringList ServerAOPacket::getContent()
{
  return m_content;
}

QString ServerAOPacket::toString()
{
  if (!isPacketEscaped() && !(getPacketInfo().header == "LE"))
  {
    // We will never send unescaped data to a client, unless its evidence.
    this->escapeContent();
  }
  else
  {
    // Of course AO has SOME expection to the rule.
    this->escapeEvidence();
  }
  return QString("%1#%2#%3").arg(getPacketInfo().header, m_content.join("#"), packetFinished);
}

QByteArray ServerAOPacket::toUtf8()
{
  QString l_packet = this->toString();
  return l_packet.toUtf8();
}

void ServerAOPacket::setContentField(int f_content_index, QString f_content_data)
{
  m_content[f_content_index] = f_content_data;
}

void ServerAOPacket::escapeContent()
{
  m_content.replaceInStrings("#", "<num>").replaceInStrings("%", "<percent>").replaceInStrings("$", "<dollar>").replaceInStrings("&", "<and>");
  this->setPacketEscaped(true);
}

void ServerAOPacket::unescapeContent()
{
  m_content.replaceInStrings("<num>", "#").replaceInStrings("<percent>", "%").replaceInStrings("<dollar>", "$").replaceInStrings("<and>", "&");
  this->setPacketEscaped(false);
}

void ServerAOPacket::escapeEvidence()
{
  m_content.replaceInStrings("#", "<num>").replaceInStrings("%", "<percent>").replaceInStrings("$", "<dollar>");
  this->setPacketEscaped(true);
}

void ServerAOPacket::setPacketEscaped(bool f_packet_state)
{
  m_escaped = f_packet_state;
}

bool ServerAOPacket::isPacketEscaped()
{
  return m_escaped;
}

void ServerAOPacket::registerPackets()
{
  PacketFactory::registerClass<PacketAskchaa>("askchaa");
  PacketFactory::registerClass<PacketCasea>("CASEA");
  PacketFactory::registerClass<PacketCC>("CC");
  PacketFactory::registerClass<PacketCH>("CH");
  PacketFactory::registerClass<PacketCT>("CT");
  PacketFactory::registerClass<PacketDE>("DE");
  PacketFactory::registerClass<PacketEE>("EE");
  PacketFactory::registerClass<PacketHI>("HI");
  PacketFactory::registerClass<PacketHP>("HP");
  PacketFactory::registerClass<PacketID>("ID");
  PacketFactory::registerClass<PacketMC>("MC");
  PacketFactory::registerClass<PacketMS>("MS");
  PacketFactory::registerClass<PacketPE>("PE");
  PacketFactory::registerClass<PacketPW>("PW");
  PacketFactory::registerClass<PacketRC>("RC");
  PacketFactory::registerClass<PacketRD>("RD");
  PacketFactory::registerClass<PacketRM>("RM");
  PacketFactory::registerClass<PacketRT>("RT");
  PacketFactory::registerClass<PacketSetcase>("SETCASE");
  PacketFactory::registerClass<PacketZZ>("ZZ");
}
