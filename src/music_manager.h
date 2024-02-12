//////////////////////////////////////////////////////////////////////////////////////
//    akashi - a server for Attorney Online 2                                       //
//    Copyright (C) 2020  scatterflower                                             //
//                                                                                  //
//    This program is free software: you can redistribute it and/or modify          //
//    it under the terms of the GNU Affero General Public License as                //
//    published by the Free Software Foundation, either version 3 of the            //
//    License, or (at your option) any later version.                               //
//                                                                                  //
//    This program is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of                //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 //
//    GNU Affero General Public License for more details.                           //
//                                                                                  //
//    You should have received a copy of the GNU Affero General Public License      //
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.        //
//////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QHash>
#include <QMap>
#include <QObject>
#include <QPair>

#include "network/aopacket.h"
#include "typedefs.h"

class ConfigManager;

class MusicManager : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Constructor for the server-wide musiclist manager.
   *
   * @param Copy of the server musiclist generated by ConfigManager::musiclist();
   */
  MusicManager(QStringList f_cdns, MusicList f_root_list, QStringList f_root_ordered, QObject *parent = nullptr);

  /**
   * @brief Destructor for the server-wide musiclist manager.
   */
  virtual ~MusicManager();

  /**
   * @brief Returns a musiclist with aliased names.
   *
   * @return See short description.
   */
  QStringList musiclist(int f_area_id);

  /**
   * @brief Returns only the root musiclist with aliased names.
   *
   */
  QStringList rootMusiclist();

  /**
   * @brief Adds a new area to the music_manager.
   *
   * @param f_area_id ID of the new area being added.
   *
   * @return Returns false if registering the area fails.
   */
  bool registerArea(int f_area_id);

  /**
   * @brief Validates the song candidate to be played. If validation fails, false is returned.
   *
   * @param f_song_name The song to be played. Can be an http/https stream or a local file.
   *
   * @param f_approved_cdns A list of approved remote content sources.
   *
   * @return Wether or not the song can be played or added.
   */
  bool validateSong(QString f_song_name, QStringList f_approved_cdns);

  /**
   * @brief Attempts to add the new song to the custom musiclist.
   *
   * @param f_song_name Friendly name shown in the clients musiclist.
   *
   * @param f_real_name Real name/url of the file.
   *
   * @param f_duration Playtime of the musicfile in seconds.
   *
   * @param f_area_id Area id of the clients current area.
   *
   * @return Returns true on success, false on fail.
   */
  bool addCustomSong(QString f_song_name, QString f_real_name, int f_duration, int f_area_id);

  /**
   * @brief Attempts to add the new category to the custom musiclist.
   *
   * @param f_category_name Category name candidate.
   *
   * @return Returns true on saccess, false on fail.
   */
  bool addCustomCategory(QString f_category_name, int f_area_id);

  /**
   * @brief Removes either a song or a category from the custom list.
   *
   * @param Name of the category or song to remove
   *
   * @return True on success, false on failure.
   */
  bool removeCategorySong(QString f_songcategory_name, int f_area_id);

  /**
   * @brief Toggles wether the root list is included for this area.
   * This also delets the custom llist if it was enabled prior.
   *
   * @return Current state of the music list.
   */
  bool toggleRootEnabled(int f_area_id);

  /**
   * @brief Removes conflicting songnames from the custom list.
   *
   * @param f_area_id Id of the area this is invoked in.
   */
  void sanitiseCustomList(int f_area_id);

  /**
   * @brief Removes all entries from the custom list.
   * @param f_area_id Id of the area custom list.
   */
  void clearCustomList(int f_area_id);

  /**
   * @brief Returns song information necessary for the operation of the jukebox.
   * @param Alias name of the song.
   * @param Area of the jukebox checking for information.
   * @return Returns a QPair with the true name and duration of the invoked song.
   */
  QPair<QString, int> songInformation(QString f_song_name, int f_area_id);

  /**
   * @brief Checks if a song is part of the clients current area custom list.
   *
   * @return Returns true if the song exists as a custom song.
   */
  bool isCustom(int f_area_id, QString f_song_name);

public slots:

  /**
   * @brief Updates the root musiclist and CDN list.
   */
  void reloadRequest();

  /**
   * @brief Triggers sending of FM packet to client joining a new area.
   */
  void userJoinedArea(int f_area_index, int f_user_id);

signals:

  /**
   * @brief Sends the FM packet with the musiclist of the area when a client enters.
   *
   * @param f_packet FM packet with the full musiclist, when enabled, and custom list.
   *
   * @param f_user_id temporary userid of the incoming client.
   */
  void sendFMPacket(AOPacket *f_packet, int f_user_id);

  /**
   * @brief Sends the FM packet with the musiclist of the area when changes are made.
   *
   * @param f_packet FM packet with the full musiclist, when enabled, and eventual custom list.
   *
   * @param f_area_index Index of the current area the edit is made in.
   */
  void sendAreaFMPacket(AOPacket *f_packet, int f_area_index);

private:
  /**
   * @brief Contains all custom lists of all areas in the server.
   */
  QHash<int, MusicList> *m_custom_lists;

  /**
   * @brief Server musiclist shared among all areas.
   */
  MusicList m_root_list;

  /**
   * @brief QList with the ordered musiclist.
   */
  QStringList m_root_ordered;

  /**
   * @brief Contains all custom songs ordered in a per-area buffer.
   */
  QMap<int, QStringList> m_customs_ordered;

  /**
   * @brief Wether the global musiclist is prepend and validation when adding custom music.
   */
  QHash<int, bool> m_global_enabled;

  /**
   * @brief Contains all server approved content sources.
   */
  QStringList m_cdns;
};
