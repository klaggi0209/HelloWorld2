(function($) {


    var hash = window.location.hash;

    $(document).ready(function() {

        if( !!hash && hash.length > 0 )
        {
            $('html,body').animate({
                scrollTop: ($(hash).offset().top - 70)
            }, 10);
        }

        $('#sidebar-nav .nav').collectHeadlines(3);

        $('h1, h2, h3').not('[data-link="ignore"]').appendLink();

        $('body').scrollspy({
            target: '#sidebar-nav',
            offset: 90
        });

        $('a').not('[role="tab"]').each(function(i, link) {
            var $link = $(link);
            if( $link.attr('href').charAt(0) == '#' )
            {
                $link.click(function(e) {
                    e.preventDefault();
                    var $target = $( $link.attr('href') );
                    $('html,body').animate({
                        scrollTop: ($target.offset().top - 70)
                    }, 300);

                    var match = $link.attr('href').match(/^(.*)(#.*)$/);
                    if( !!match && match.length > 2 )
                    {
                        window.location.hash = match[2];
                    }
                });
            }
        });



        /*
        $('body').scrollspy({
            target: '.nav.nav-list li ul',
            offset: 70
        });
        */

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

    $.fn.appendLink = function()
    {
        this.each(function(i, elem) {
            if( $(elem).parents('.panel-example').length > 0 )
            {
                // skip
                return true;
            }
            var id = $(elem).getIdForced();
            $(elem).addClass('has-hover');
            $(elem).append(
                $('<a href="#' + id + '" class="text-muted hover-visible text-small"><span class="glyphicon glyphicon-link"></span></a>')
            )
        });
    };

    $.fn.collectHeadlines = function( maxDepth, headlines, depth )
    {
        maxDepth = maxDepth || 1;
        depth = depth || 1;

        var $container = this;
        var headlineSelector = 'h' + depth;
        var $headlines = headlines || $(headlineSelector);

        $headlines.each( function ( i, headline ) {
            if( $(headline).parents('.panel-example').length > 0 )
            {
                // skip
                return true;
            }
            var $headline = $(headline);
            var childHeadlineSelector = 'h' + (depth+1);

            var $item = buildListItem( $headline );

            if( depth < maxDepth )
            {
                var $children = $('<ul></ul>').collectHeadlines( maxDepth, $headline.nextUntil(headlineSelector, childHeadlineSelector) , depth+1);
                $item.append( $children );
            }

            $container.append( $item );
        });

        return this;

        function buildListItem( $target )
        {
            var targetID = $target.getIdForced();
            var targetText = $target.attr('data-title') || $target.text();

            var $item = $('<li></li>');
            $item.append('<a href="#' + targetID + '">' + targetText + '</a>');

            $item.find('a').click(function(e) {
                e.preventDefault();
                $('html,body').animate({
                    scrollTop: ($target.offset().top - 70)
                }, 300);
            });

            return $item;
        }

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