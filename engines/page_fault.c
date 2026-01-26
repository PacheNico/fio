/*
 * page_fault engine
 *
 * IO engine that reads/writes from files by causing page faults
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#include "../fio.h"

//struct page_faultio_data {
//    void *mmap_ptr;
//    size_t mmap_sz;
//    off_t mmap_off;
//};

static int fio_page_faultio_init(struct thread_data *td)
{
	return 0;
}

static int fio_page_faultio_prep(struct thread_data *td, struct io_u *io_u)
{
    struct fio_file *f;
    //struct page_faultio_data *pfd;

    if (io_u->file)
        return 0;

    if (!td->files_index) {
        dprint(FD_IO, "page_faultio_prep: no files\n");
        return 1;
    }

    f = td->files[0];
    io_u->file = f;

    //pfd = FILE_ENG_DATA(f);
    //if (!pfd) {
    //     dprint(FD_IO, "page_faultio_prep: no engine data\n");
    //     return 1;
    // }

    //io_u->buflen = td->o.min_bs[DDIR_READ];
    //if (!io_u->buflen)
    //    io_u->buflen = 4096;
//
    //io_u->offset = pfd->mmap_off;
    //io_u->ddir = DDIR_READ;
//
    //if (io_u->offset + io_u->buflen > pfd->mmap_sz) {
    //    dprint(FD_IO, "page_faultio_prep: wrap around offset\n");
    //    io_u->offset = 0;
    //    pfd->mmap_off = 0;
    //}

    return 0;
}

static enum fio_q_status fio_page_faultio_queue(struct thread_data *td, struct io_u *io_u)
{
    //struct page_faultio_data *pfd = FILE_ENG_DATA(io_u->file);
    void *ptr;
    size_t i;
    ptr = (void *) td->orig_buffer + io_u->offset;
    dprint(FD_IO, "page_faultio_queue: ptr: %p, offset: %llu, xfer_buflen: %llu\n", ptr, io_u->offset, io_u->xfer_buflen);
    switch (io_u->ddir) {
    case DDIR_WRITE:
        dprint(FD_IO, "page_faultio_queue: write\n");
        for (i = 0; i < io_u->xfer_buflen; i++) {
            ((unsigned char *) ptr)[i] = ((unsigned char *) io_u->xfer_buf)[i];
        }
        //pfd->mmap_off += io_u->xfer_buflen;
        return FIO_Q_COMPLETED;
    case DDIR_READ:
        dprint(FD_IO, "page_faultio_queue: read\n");
        for (i = 0; i < io_u->xfer_buflen; i++) {
            ((unsigned char *) io_u->xfer_buf)[i] = ((unsigned char *) ptr)[i];
        }
        //pfd->mmap_off += io_u->xfer_buflen;
        return FIO_Q_COMPLETED;
    default:
        dprint(FD_IO, "page_faultio_queue: DEFAULT\n");
        return FIO_Q_COMPLETED;
    }
}

static int fio_page_faultio_open_file(struct thread_data *td, struct fio_file *f)
{
	return 0;
}

static int fio_page_faultio_close_file(struct thread_data *td, struct fio_file *f)
{
	return 0;
}

static int fio_page_faultio_get_file_size(struct thread_data *td, struct fio_file *f)
{
	uint64_t size = f->real_file_size;

	return 0;
}

static int fio_page_faultio_setup(struct thread_data *td)
{
    struct fio_file *f;
    //struct page_faultio_data *pfd;
    unsigned int i;

    if (!td->files_index) {
        add_file(td, "page_fault", 0, 0);
        td->o.nr_files = td->o.nr_files ? : 1;
        td->o.open_files++;
    }

    for (i = 0; i < td->o.nr_files; i++) {
        f = td->files[i];
        //pfd = malloc(sizeof(struct page_faultio_data));
        //if (!pfd)
        //    return -1;

        //pfd->mmap_ptr = td->orig_buffer;
        //pfd->mmap_sz = td->mmap_size;
        //pfd->mmap_off = 0;
        //FILE_SET_ENG_DATA(f, pfd);
    }

    return 0;
}

static void fio_page_faultio_cleanup(struct thread_data *td)
{
    struct fio_file *f;
    unsigned int i;

    for (i = 0; i < td->o.nr_files; i++) {
        f = td->files[i];
        if (FILE_ENG_DATA(f)) {
            free(FILE_ENG_DATA(f));
            FILE_SET_ENG_DATA(f, NULL);
        }
    }
}

static struct ioengine_ops ioengine = {
	.name		= "page_fault",
	.version	= FIO_IOOPS_VERSION,
	.init		= fio_page_faultio_init,
	.prep		= fio_page_faultio_prep,
	.queue		= fio_page_faultio_queue,
	.open_file	= fio_page_faultio_open_file,
	.close_file	= fio_page_faultio_close_file,
	.get_file_size	= fio_page_faultio_get_file_size,
	.setup		= fio_page_faultio_setup,
	.cleanup	= fio_page_faultio_cleanup,
	.flags		= FIO_NOEXTEND | FIO_SYNCIO | FIO_DISKLESSIO | FIO_PAGE_FAULT,
};

static void fio_init fio_page_faultio_register(void)
{
	register_ioengine(&ioengine);
}

static void fio_exit fio_page_faultio_unregister(void)
{
	unregister_ioengine(&ioengine);
}