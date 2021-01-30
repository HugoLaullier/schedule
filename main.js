const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

$(document).ready(function(){
    $.getJSON("./json/out/res.json", function(data){
        draw_table(data);
    }).fail(function(){
        console.log("An error has occurred.");
    });
});

function draw_table(data) {
    // init
    const nb_promotions = data['schedule']['day_1']['slot_1'].length;
    const offset_x = 10;
    const offset_y = 90;
    const cell_height = 100;
    const cols = 5;
    const rows = 4;
    const scale = 1000/(Math.max(cols,rows));
    const width = canvas.width = window.innerWidth - 20;
    const height = canvas.height = nb_promotions*rows*cell_height + 
        offset_y*2 + ((nb_promotions-1)*offset_y);
    const cell_width = (width - offset_x*2)/(cols+1);
    let x = offset_x + cell_width;
    let y = offset_y;

    // draw table
    for (let k = 0; k < nb_promotions; k++) {
        ctx.font = '20px serif';
        ctx.fillStyle = "black";
        ctx.fillText(data['schedule']['day_1']['slot_1'][k].training + ' '
            + data['schedule']['day_1']['slot_1'][k].promo_id.toString()
            + ' - group ' + data['schedule']['day_1']['slot_1'][k].group_id, 
            5 + offset_x, offset_y*(k+1) + rows*cell_height*k- 20);
        for (let i = 0; i < cols; i++) {
            ctx.fillStyle = "gray";
            ctx.fillRect(x + i*cell_width, offset_y*(k+1) 
            + rows*cell_height*k - 45, cell_width, offset_y - 45);
            ctx.rect(x + i*cell_width, offset_y*(k+1) 
            + rows*cell_height*k - 45, cell_width, offset_y - 45);
            ctx.lineWidth = 2;
            ctx.strokeStyle = "black";
            ctx.stroke();
            let day;
            switch (i) {
                case 0: day = "Monday";    break;
                case 1: day = "Tuesday";   break;
                case 2: day = "Wednesday"; break;
                case 3: day = "Thursday";  break;
                case 4: day = "Friday";    break;
            }
            ctx.fillStyle = "black";
            ctx.fillText(day, x + i*cell_width + 5, 
                offset_y*(k+1) + rows*cell_height*k - 20);
        }
        for (let i = 0; i < rows; i++) {
            ctx.fillStyle = "gray";
            ctx.fillRect(offset_x, offset_y*(k+1) + i*cell_height
                + rows*cell_height*k, cell_width, cell_height);
            ctx.rect(offset_x, offset_y*(k+1) + i*cell_height
                + rows*cell_height*k, cell_width, cell_height);
            ctx.lineWidth = 2;
            ctx.strokeStyle = "black";
            ctx.stroke();
            let slot;
            switch (i) {
                case 0: slot = "8:00 am - 10:00 am";  break;
                case 1: slot = "10:00 am - 12:00 am"; break;
                case 2: slot = "14:00 pm - 16:00 pm"; break;
                case 3: slot = "16:00 pm - 18:00 pm"; break;
            }
            ctx.fillStyle = "black";
            ctx.fillText(slot, offset_x + 5 , offset_y*(k+1) + i*cell_height
            + rows*cell_height*k + 20);
        }
    }
    for (let i = 0; i < cols; i++) {
        for (let j = 0; j < rows; j++) {
            for (let k = 0; k < nb_promotions; k++) {
                y = offset_y*(k+1) + rows*cell_height*k + j * cell_height;
                switch (data['schedule']['day_' + (i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].subject) {
                    case "Computer-Science" :
                        ctx.fillStyle = "lightgreen";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "Physics" :
                        ctx.fillStyle = "orange";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "Mathematics" :
                        ctx.fillStyle = "yellow";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    case "English" :
                        ctx.fillStyle = "lightblue";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                    default :
                        ctx.fillStyle = "lightgray";
                        ctx.fillRect(x, y, cell_width, cell_height);
                        break;
                }
                if (data['schedule']['day_' + (i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_id !== -1) {
                    ctx.font = '20px serif';
                    ctx.fillStyle = "black";
                    ctx.fillText(data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].subject + ' ' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_type, x+5, y+25);
                    ctx.fillText('Room n°' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].room_id, x+5, y+50);
                    ctx.fillText('Teacher n°' +
                        data['schedule']['day_'+(i+1).toString()]
                        ['slot_'+ (j+1).toString()][k].teacher_id, x+5, y+75);
                }
                ctx.rect(x, y, cell_width, cell_height);
                ctx.lineWidth = 2;
                ctx.strokeStyle = "black";
                ctx.stroke();
            }
        }
        x += cell_width;
    }
}