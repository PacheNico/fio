Name:           fio
Version:        3.50
Release:        1%{?dist}
Summary:        Flexible I/O Tester

License:        GPL-2.0-only
URL:            https://github.com/PacheNico/fio
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  zlib-devel
BuildRequires:  libaio-devel
BuildRequires:  python3
BuildRequires:  rdma-core-devel
BuildRequires:  numactl-devel
BuildRequires:  libcurl-devel
BuildRequires:  openssl-devel

%description
fio is an I/O tool meant to be used both for benchmark and stress/hardware
verification. It supports a number of I/O engines, I/O priorities, bandwidth
and latency logging, and a variety of parameters to simulate any given I/O
workload.

This build includes the page_fault mmap-backed ioengine for anonymous fault
benchmarking.

%prep
%setup -q -n %{name}-%{version}

%build
./configure --prefix=%{_prefix}
%make_build

%install
%make_install prefix=%{_prefix} mandir=%{_mandir} DESTDIR=%{buildroot}

%files
%license COPYING
%doc README.rst HOWTO.rst MORAL-LICENSE
%{_bindir}/fio
%{_bindir}/fio_generate_plots
%{_bindir}/fio2gnuplot
%{_bindir}/genfio
%{_bindir}/fiologparser.py
%{_bindir}/fiologparser_hist.py
%{_bindir}/fio-histo-log-pctiles.py
%{_bindir}/fio_jsonplus_clat2csv
%{_bindir}/fio-btrace2fio
%{_bindir}/fio-dedupe
%{_bindir}/fio-verify-state
%{_bindir}/fio-genzipf
%{_mandir}/man1/fio.1*
%{_mandir}/man1/fio_generate_plots.1*
%{_mandir}/man1/fio2gnuplot.1*
%{_mandir}/man1/fiologparser_hist.py.1*
%{_datadir}/fio/

%changelog
* Tue Mar 10 2026 Nico Pache <npache@redhat.com> - 3.50-1
- Build from git snapshot with page_fault ioengine
