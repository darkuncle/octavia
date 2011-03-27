/**
 * Octavia filesystem, FUSE client implemenation.
 *
 * gcc -Wall `pkg-config fuse --cflags --libs` octavia-fuse.c -o 8va
 */

#define FUSE_USE_VERSION 26

#ifdef linux
/* For pread()/pwrite() */
#define _XOPEN_SOURCE 500
#endif

#include <sys/time.h>
#include <sys/types.h>

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

#include "util.h"


int octavia_getattr(const char * path, struct stat * status) {
      memset(status, 0, sizeof *status);

      /* Use the directory descriptor associated with the path to find the
       * file metadata for the path. Most struct stat items will be blank,
       * but mtime, size, and mode will be filled. mode is limited to
       * S_IFDIR | 0755 or S_IFREG | 0644. We also have to fill in nlink;
       * the FUSE FAQ says 1 is acceptable, otherwise # sub dirs + 2. */

      /* TODO */

      return 0;
}


/**
 * @return 0, if the path exists, ENOENT otherwise. Octavia is not
 * POSIX-compliant, so the mask is treated as if it were F_OK.
 */
int octavia_access(const char * path, int mask) {
      /* TODO */

      return 0;
}


/**
 * @return ENOTSUP.
 */
int octavia_readlink(const char * path, char * buf, size_t size) {
      (void) path;
      memset(buf, 0, size);
      return -ENOTSUP;
}


int octavia_readdir(const char * path, void * buf, fuse_fill_dir_t filler, off_t offset,
                    struct fuse_file_info * fi)
{
      /* TODO */

      return 0;
}


/**
 * @return ENOTSUP.
 */
int octavia_mknod(const char * path, mode_t mode, dev_t rdev) {
      (void) path;
      (void) mode;
      (void) rdev;
      return -ENOTSUP;
}


int octavia_mkdir(const char * path, mode_t mode) {
      /* Ensure that d = dirname(path) exists given the directory descriptor
       * for path. Create a new empty directory descriptor for basename(path),
       * update the descriptor for d and all parents. */

      /* TODO */

      return 0;
}


int octavia_unlink(const char * path) {
      /* Ensure that path exists. Create new directory descriptor for
       * d = dirname(path) that lacks basename(path), update d and all
       * parents. */

      /* TODO */

      return 0;
}


int octavia_rmdir(const char * path) {
      /* Ensure that path exists, is a directory, and is empty. Create a new
       * directory descriptor for d = dirname(path) that lacks basename(path),
       * update d and all parents. */

      /* TODO. Should share substantial parts of implementation with
       * o_unlink. */

      return 0;
}


/**
 * @return ENOTSUP.
 */
int octavia_symlink(const char * from, const char * to) {
      (void) from;
      (void) to;
      return -ENOTSUP;
}


int octavia_rename(const char * from, const char * to) {
      /* Ensure that from exists, that if to exists it is the same type as
       * from (dir or file), that dirname(to) exists. Update dirname(from)
       * and all parents. */

      /* TODO */

      return 0;
}


/**
 * @return ENOTSUP. Octavia does not support multiple hard links.
 */
int octavia_link(const char * from, const char * to) {
      (void) from;
      (void) to;
      return -ENOTSUP;
}


/**
 * @return ENOTSUP. File mode is largely meaningless in Octavia (only
 * S_IFREG and S_IFDIR have any meaning).
 */
int octavia_chmod(const char * path, mode_t mode) {
      (void) path;
      (void) mode;
      return -ENOTSUP;
}


/**
 * @return ENOTSUP. File ownership is meaningless in Octavia.
 */
int octavia_chown(const char * path, uid_t uid, gid_t gid) {
      (void) path;
      (void) uid;
      (void) gid;
      return -ENOTSUP;
}


int octavia_truncate(const char * path, off_t size) {
      /* Ensure that path exists and is a file. Truncate it. */

      /* TODO */

      return 0;
}


int octavia_utimens(const char * path, const struct timespec ts [2]) {
      /* TODO */

      return 0;
}


int octavia_open(const char * path, struct fuse_file_info * fi) {
      /* TODO */

      return 0;
}


int octavia_read(const char * path, char * buf, size_t size, off_t offset,
                 struct fuse_file_info * fi)
{
      /* TODO */

      return 0;
}


int octavia_write(const char * path, const char * buf, size_t size, off_t offset,
                  struct fuse_file_info * fi)
{
      /* TODO */

      return 0;
}


int octavia_statfs(const char * path, struct statvfs * status) {
      /*
       * Future: Maybe different versions of Octavia will have different
       * limits and values. In this case, get the descriptor for path.
       */
      (void) path;

      memset(status, 0, sizeof *status);
      status->f_namemax = NameSize;
      status->f_bsize = DefaultSegmentSize;
      /*status->f_flags = ST_NOSUID;*/ /* Not on Darwin */

      return 0;
}


int octavia_release(const char * path, struct fuse_file_info * fi) {
      (void) path;
      (void) fi;

      return 0;
}


int octavia_fsync(const char * path, int isdatasync, struct fuse_file_info * fi) {
      (void) path;
      (void) isdatasync;
      (void) fi;

      return 0;
}


#ifdef HAVE_SETXATTR

/**
 * @return ENOTSUP.
 */
int octavia_setxattr(const char * path, const char * name, const char * value, size_t size,
                     int flags)
{
      return -ENOTSUP;
}

/**
 * @return ENOTSUP.
 */
int octavia_getxattr(const char * path, const char * name, char * value, size_t size) {
      return -ENOTSUP;
}

/**
 * @return ENOTSUP.
 */
int octavia_listxattr(const char * path, char * list, size_t size) {
      return -ENOTSUP;
}

/**
 * @return ENOTSUP.
 */
int octavia_removexattr(const char * path, const char * name) {
      return -ENOTSUP;
}

#endif /* HAVE_SETXATTR */


struct fuse_operations OctaviaOperations = {
      .getattr          = octavia_getattr,
      .access           = octavia_access,
      .readlink         = octavia_readlink,
      .readdir          = octavia_readdir,
      .mknod            = octavia_mknod,
      .mkdir            = octavia_mkdir,
      .symlink          = octavia_symlink,
      .unlink           = octavia_unlink,
      .rmdir            = octavia_rmdir,
      .rename           = octavia_rename,
      .link             = octavia_link,
      .chmod            = octavia_chmod,
      .chown            = octavia_chown,
      .truncate         = octavia_truncate,
      .utimens          = octavia_utimens,
      .open             = octavia_open,
      .read             = octavia_read,
      .write            = octavia_write,
      .statfs           = octavia_statfs,
      .release          = octavia_release,
      .fsync            = octavia_fsync,
#ifdef HAVE_SETXATTR
      .setxattr         = octavia_setxattr,
      .getxattr         = octavia_getxattr,
      .listxattr        = octavia_listxattr,
      .removexattr      = octavia_removexattr,
#endif
};


int main(int argc, char * argv []) {
      umask(0);
      return fuse_main(argc, argv, &OctaviaOperations, NULL);
}

