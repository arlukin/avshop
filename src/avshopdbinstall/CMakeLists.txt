add_executable(avshopdbinstall 
	Main.cpp
)

target_link_libraries (avshopdbinstall
        soci_mysql-gcc-3_0       
        avutils
        avshopbackend
        ${EXTRA_LIBS}
)

install (TARGETS avshopdbinstall DESTINATION bin)

