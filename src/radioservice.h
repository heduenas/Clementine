/* This file is part of Clementine.

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RADIOSERVICE_H
#define RADIOSERVICE_H

#include <QObject>
#include <QList>
#include <QUrl>

#include "radioitem.h"
#include "multiloadingindicator.h"

class Song;
class RadioModel;

class RadioService : public QObject {
  Q_OBJECT

 public:
  RadioService(const QString& name, RadioModel* model);
  virtual ~RadioService() {}

  QString name() const { return name_; }
  RadioModel* model() const { return model_; }

  virtual RadioItem* CreateRootItem(RadioItem* parent) = 0;
  virtual void LazyPopulate(RadioItem* item) = 0;

  virtual QUrl UrlForItem(const RadioItem* item) const;
  virtual QString TitleForItem(const RadioItem* item) const;
  virtual QString ArtistForItem(const RadioItem* item) const;

  virtual void ShowContextMenu(RadioItem* item, const QModelIndex& index,
                               const QPoint& global_pos) {
    Q_UNUSED(item); Q_UNUSED(index); Q_UNUSED(global_pos); }

  virtual void StartLoading(const QUrl& url) = 0;
  virtual void LoadNext(const QUrl& url);

  virtual bool IsPauseAllowed() const { return true; }
  virtual bool ShowLastFmControls() const { return false; }

  virtual void ReloadSettings() {}

  virtual QString Icon() { return QString(); }

 signals:
  void TaskStarted(MultiLoadingIndicator::TaskType);
  void TaskFinished(MultiLoadingIndicator::TaskType);

  void StreamReady(const QUrl& original_url, const QUrl& media_url);
  void StreamFinished();
  void StreamError(const QString& message);
  void StreamMetadataFound(const QUrl& original_url, const Song& song);

  void AddItemToPlaylist(RadioItem* item);

 private:
  RadioModel* model_;
  QString name_;
};

#endif // RADIOSERVICE_H
