(function($) {


    $(document).ready(function() {


        $('#sidebar-nav .nav').buildSidebarNav();

        $('body').scrollspy({
            target: '#sidebar-nav',
            offset: 70
        });

        $('body').scrollspy({
            target: '.nav.nav-list li ul',
            offset: 70
        });


        $('.nav.nav-list li').on('activate.bs.scrollspy', function (event) {
            var elem = $(event.target);
            elem.find('ul').show();
            elem.prev('li' ).find('ul').hide();
        });


        $('[data-scrollTo]').each(function(i, elem) {
            var $elem = $( elem );

            $elem.click( function( e ) {
                var selector = $elem.attr('data-scrollTo');
                var scrollOffset = parseInt( $(selector).attr('data-scrollOffset') );
                var targetOffset;


                e.preventDefault();

                if( $.isNumeric( selector ) )
                {
                    targetOffset = parseInt( selector );
                }
                else
                {
                    targetOffset = $( selector ).offset().top;
                }

                $('html,body').animate({
                    scrollTop: (targetOffset - scrollOffset)
                }, 300);
            });

        });

    });

    $.fn.buildSidebarNav = function()
    {
        var list = this;
        $('h1').each(function(i, section) {
            var $section = $(section);
            var sectionId = $section.getIdForced();
            var listItem = $('<li><a href="#' + sectionId + '">' + $section.text() + '</a></li>');

            listItem.find('a').click(function(e) {
                e.preventDefault();
                $('html,body').animate({
                    scrollTop: ($section.offset().top - 70)
                }, 300);
            });

            var subList = $('<ul></ul>');
            $section.nextUntil('h1').filter('h2').each(function(j, subSection) {
                var $subSection = $(subSection);
                var subSectionId = $subSection.getIdForced();
                var subListItem = $( '<li><a href="#'+subSectionId+'">' + $subSection.text() + '</a></li>' );

                subListItem.find('a').click(function(e) {
                    e.preventDefault();
                    $('html,body').animate({
                        scrollTop: ($subSection.offset().top - 70)
                    }, 300);
                });

                subList.append( subListItem );
            });

            if( subList.find('li').length > 0 ) {
                listItem.append(subList);
            }

            list.append(listItem);
        });
    };

    var idCount = 0;
    $.fn.getIdForced = function() {
        if( !this.attr('id') || this.attr('id').length <= 0 )
        {
            this.attr('id', 'element_'+idCount);
            idCount++;
        }
        return this.attr('id');
    }

}(jQuery));