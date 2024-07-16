/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OCEABASE_STORAGE_LS_RESTORE_TASK_MGR_H
#define OCEABASE_STORAGE_LS_RESTORE_TASK_MGR_H
#include "ob_ls_restore_args.h"
#include "share/restore/ob_ls_restore_status.h"
#include "storage/high_availability/ob_storage_restore_struct.h"

namespace oceanbase
{
namespace storage
{

class ObILSRestoreState;
class ObLSRestoreTaskMgr final
{
public:
  static const int64_t OB_RESTORE_MAX_DAG_NET_NUM = 5;
  static const int64_t OB_LS_RESTORE_MAX_TABLET_NUM = 10000;
  // tablets number in one dag net for low priority tablets.
  static const int64_t LOW_PRI_TABLETS_BATCH_NUM = 64;
  // tablets number in one dag net for high priority tablets.
  static const int64_t HIGH_PRI_TABLETS_BATCH_NUM = 1024;

  // There are 2 kinds of types during restore. One is log stream restore
  // task at phase RESTORE_SYS_TABLETS, which does not have any tablets in
  // ToRestoreTabletGroup. The other is tablet group restore task at phase
  // RESTORE_TABLETS_META, RESTORE_TO_CONSISTENT_SCN, QUICK_RESTORE,
  // or RESTORE_MAJOR_DATA.
  enum TaskType
  {
    TABLET_GROUP_RESTORE_TASK = 0,
    LS_RESTORE_TASK
  };

  enum ToRestoreFromQType
  {
    FROM_WAIT_TABLETS_Q = 0, // from wait_tablet_set_
    FROM_HIGH_PRI_WAIT_TABLETS_Q, // from high_pri_wait_tablet_set_
    FROM_NONE, // use for ls restore
  };

  // To restore tablet group returned by 'choose_tablets_to_restore'.
  class ToRestoreTabletGroup final
  {
    friend class ObLSRestoreTaskMgr;

  public:
    ToRestoreTabletGroup() :
        tablet_list_(),
        action_(ObTabletRestoreAction::MAX),
        from_q_type_(ToRestoreFromQType::FROM_NONE),
        need_redo_failed_tablets_(true),
        task_type_(TaskType::TABLET_GROUP_RESTORE_TASK) {}
    const ObSArray<common::ObTabletID> &get_tablet_list() const { return tablet_list_; }
    ObTabletRestoreAction::ACTION action() const { return action_; }
    ToRestoreFromQType from_q_type() const { return from_q_type_; }
    bool empty() const { return tablet_list_.empty(); }
    int64_t count() const { return tablet_list_.count(); }
    bool need_redo_failed_tablets() const { return need_redo_failed_tablets_; }
    TaskType task_type() const { return task_type_; }
    bool is_tablet_group_task() const
    {
      return TaskType::TABLET_GROUP_RESTORE_TASK == task_type_;
    }

    int assign(const ToRestoreTabletGroup &tg);

    TO_STRING_KV(K_(tablet_list), K_(action), K_(from_q_type), K_(need_redo_failed_tablets), K_(task_type));

  private:
    ObSArray<common::ObTabletID> tablet_list_;
    ObTabletRestoreAction::ACTION action_;
    // From wait_tablet_set_ or high_pri_wait_tablet_set_
    ToRestoreFromQType from_q_type_;
    // In case of leader switch, the restoring tablets from old leader may
    // have not been restored on new leader. Therefore, we discard the failed
    // tablets after task finish.
    bool need_redo_failed_tablets_;
    TaskType task_type_;
  };

  using TaskMap = common::hash::ObHashMap<share::ObTaskId, ToRestoreTabletGroup, common::hash::NoPthreadDefendMode>;
  using TabletSet = common::hash::ObHashSet<common::ObTabletID>;
public:
  ObLSRestoreTaskMgr();
  ~ObLSRestoreTaskMgr();
  int init(ObILSRestoreState *state_handler, const share::ObLSID &ls_id);
  void destroy();
  // receive restored tablets from leader
  int add_tablet_in_wait_set(
      const ObIArray<common::ObTabletID> &tablet_ids);
  // PENDING tablets generated by transfer
  int record_one_tablet_to_restore(
      const common::ObTabletID& tablet_id);

  // choose some tablets to restore.
  // Note: not remove from to do list.
  int choose_tablets_to_restore(ToRestoreTabletGroup &tablet_group);

  // schedule the pre choosed tablets to restore.
  int schedule_tablet_group_restore(
      const share::ObTaskId &task_id,
      const ToRestoreTabletGroup &to_restore_tg,
      bool &reach_dag_limit);
  
  int schedule_ls_restore(
      const share::ObTaskId &task_id);

  // handle restoring task, check if some task is finish, and returned the restored tablets.
  int remove_restored_tablets(ObIArray<common::ObTabletID> &restored_tablets);
  int reload_get_unfinished_tablets(
      ObIArray<common::ObTabletID> &unfinished_high_pri_tablets,
      ObIArray<common::ObTabletID> &unfinished_tablets) const;
  int cancel_task();
  bool is_restore_completed() const;

  void set_force_reload();

  void clear_tablets_to_restore();
  void clear_all();

  bool has_no_tablets_to_restore() const;
  bool has_no_tablets_restoring() const;

  // Current ls switch from follower to leader.
  void switch_to_leader();
  // Current ls switch from leader to follower.
  void switch_to_follower();
  // Leader switched, and current ls is still a follower.
  void leader_switched();

private:
  int choose_tablets_from_wait_set_(storage::ObLS &ls, ToRestoreTabletGroup &tablet_group);
  int choose_tablets_from_high_pri_tablet_set_(storage::ObLS &ls, ToRestoreTabletGroup &tablet_group);
  int check_task_exist_(const share::ObTaskId &task_id, bool &is_exist);
  int check_tablet_status_(
      storage::ObLS &ls,
      const common::ObTabletID &tablet_id,
      bool &is_exist,
      bool &is_restored,
      ObTabletRestoreStatus::STATUS &restore_status) const;

  int check_transfer_start_finish_(const ObTabletHandle &tablet_handle, bool &is_finish) const;
  int check_transfer_start_finish_(const common::ObTabletID &tablet_id, bool &is_finish) const;
  int is_tablet_restore_finish_(
    const share::ObLSRestoreStatus &ls_restore_status,
    const ObTabletHandle &tablet_handle,
    bool &is_finish) const;
  int check_tablet_is_restoring_(const common::ObTabletID &tablet_id, bool &is_restoring) const;
  int check_need_reload_tablets_(bool &reload);

  int check_tablet_need_discard_when_reload_(
      const ObTabletHandle &tablet_handle,
      bool &discard) const;

  // Discard restore the uncommitted tablet created by transfer in,
  // while the log has been recovered.
  int check_need_discard_transfer_tablet_(
      const ObTabletHandle &tablet_handle,
      bool &discard) const;

  // check tablet status is DELETED or TRANSFER_OUT_DELETED.
  int check_tablet_is_deleted_(
    const ObTabletHandle &tablet_handle,
    bool &is_deleted) const;

  // At phase QUICK_RESTORE, for tablets created by transfer, the initial status
  // is FULL. Its next status may be EMPTY if source tablet is UNDEFINED. Therefore,
  // the transfer table can only be restored from backup, rather than be replaced by
  // the table from source tablet. That is to say, for FULL tablet with transfer
  // table, there are two ways to replace it with actual table. One is from source tablet,
  // the other is from backup. We should ensure which way to use. So, when we find a FULL
  // tablet with transfer table during reload, the transfer table is first considered to be
  // replaced by table from backup. But can only be schedulered to restore before turn into EMPTY.

  // If the transfer in commit scn is smaller than the specified restore scn, the transfer table of
  // the tablet is no need to be replaced during QUICK_RESTORE.
  int check_need_discard_uncommit_transfer_tablet_(
      bool &discard) const;
  bool is_follower_() const;
  ObTabletRestoreAction::ACTION get_common_restore_action_(
      const share::ObLSRestoreStatus &ls_restore_status) const;

  int reload_tablets_();
  int handle_task_finish_(
      ObLS *ls,
      const ToRestoreTabletGroup &restored_tg,
      ObIArray<common::ObTabletID> &restored_tablets,
      ObIArray<common::ObTabletID> &high_pri_tablet_need_redo,
      ObIArray<common::ObTabletID> &wait_tablet_need_redo);

  int redo_failed_tablets_(
      ObIArray<common::ObTabletID> &high_pri_tablet_need_redo,
      ObIArray<common::ObTabletID> &wait_tablet_need_redo);
  void remove_finished_task_(const ObIArray<share::ObTaskId> &finish_task);

  void unset_force_reload_();
  void set_noneed_redo_failed_tablets_();

private:
  bool is_inited_;
  share::ObLSID ls_id_;
  lib::ObMutex mtx_;
  // The doing task.
  TaskMap tablet_map_;
  // Tablets that are restoring.
  TabletSet schedule_tablet_set_;
  // Tablets that are to do restore.
  // To restore tablets are from local tablet service for leader. However,
  // for follower, they are from leader before it has been restored.
  TabletSet wait_tablet_set_;
  // Record these tablets which should restore minor data as soon as possible.
  TabletSet high_pri_wait_tablet_set_;

  ObILSRestoreState *restore_state_handler_;
  // Force reload tablets before choose tablets to restore.
  bool force_reload_;
  // 'final_reload_' is marked as True when no tablets to restore are found after reload. Then,
  // reload is forbidden while no tablets in wait or doing set.
  bool final_reload_;
  // Follower can reload tablets only if leader has been restored. This is
  // true for restore status of RESTORE_TABLETS_META and RESTORE_MAJOR_DATA.
  bool has_checked_leader_done_;
  DISALLOW_COPY_AND_ASSIGN(ObLSRestoreTaskMgr);
};

}
}

#endif
