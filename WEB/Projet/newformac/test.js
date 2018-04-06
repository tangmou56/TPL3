h="https://scontent.cdninstagram.com/vp/81834cb42906a1ad4287a9b707f84183/5B4109F5/t51.2885-15/s150x150/e35/14334822_1806325886311084_1095502737_n.jpg"



var token = '1362124742.3ad74ca.6df307b8ac184c2d830f6bd7c2ac5644',
    num_photos = 10;

$.ajax({
    url: 'https://api.instagram.com/v1/users/self/media/recent',
    dataType: 'jsonp',
    type: 'GET',
    data: {access_token: token, count: num_photos},
    success: function(data){
        console.log(data);
        for( x in data.data ){
            $('ul').append('<li><img src="'+data.data[x].images.low_resolution.url+'"></li>');
            $('ul').append('<li>'+data.data[x].location.name+'</li>');
            $('ul').append('<li>'+data.data[x].location.latitude+'</li>');
            $('ul').append('<li>'+data.data[x].location.longitude+'</li>');
        }
    },
    error: function(data){
        console.log(data);
    }
});


