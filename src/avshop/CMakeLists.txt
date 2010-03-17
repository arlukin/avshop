add_executable(avshop 
        CheckOutPanel/CheckOutPanel.cpp
        CheckOutPanel/CheckOutPage.cpp
        CheckOutPanel/ConfirmPage.cpp
        CheckOutPanel/CompletedPage.cpp
        Widget/UserWidget.cpp
	ArticleWidget.cpp		
	ForgotPasswordPanel.cpp
	Main.cpp
	NewAccountPanel.cpp
	ProductListThumbViewWidget.cpp	
	ProductMenuItem.cpp
	ProductWidget.cpp
	ShopApplication.cpp	
)

target_link_libraries (avshop wthttp avshopbackend ${EXTRA_LIBS})

install (TARGETS avshop DESTINATION bin)

