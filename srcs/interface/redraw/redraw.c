#include "sh21.h"
#include "interface_functions.h"

static void     move_cursor_to_coord(t_interface *itf, uint64_t x, uint64_t y)
{
    int64_t x_moves;
    int64_t y_moves;

    x_moves =  ((itf->cursor.x - x) * (-1));
    y_moves =  ((itf->cursor.y - y) * (-1));

    while (x_moves-- > 0)
        tputs(itf->termcaps.left, 1, &ft_putc);

    while (x_moves++ < 0)
        tputs(itf->termcaps.right, 1, &ft_putc);

    while (y_moves-- > 0)
        tputs(itf->termcaps.down, 1, &ft_putc);

    while (y_moves++ < 0)
        tputs(itf->termcaps.up, 1, &ft_putc);
}

static void    redraw_line(t_interface *itf)
{
    uint64_t    rd_flag;

    rd_flag = itf->window.rd_flag;

    if (rd_flag & RD_NONE)
        return;

    if (rd_flag & RD_ALL)
    {
        move_cursor_to_coord(itf, 0, 0);
        //print_prompt(shell, itf->prompt.state);
        //redraw entire line
    }
    if (rd_flag & RD_LINE)
    {
        //move cursor to x/y prompt_len
        //redraw entire line
    }
    if (rd_flag & RD_LAST)
    {
        //move cursor to x/y prompt_len + lin_len - 1
        //print last char of line vector
    }


    if (rd_flag & RD_FPTP)
    {
        //move cursor to Point 1
        //print line vector from p1 to p2
    }
    if (rd_flag & RD_FPTE)
    {
        //move cursor to Point 1
        //print line vector from p1 to end (?define end?)
    }
    if (rd_flag & RD_FSTP)
    {
        //move cursor to x/y prompt len
        //print line vector from start to p2
    }
}

static void     move_cursor(t_interface *itf)
{
    uint64_t    rd_flag;

    rd_flag = itf->window.rd_flag;
    
    if (rd_flag & RD_CEND)
    {

    }
    else if (rd_flag & RD_CHOME)
    {

    }
    else if (rd_flag & RD_CMOVE)
    {

    }
}

void    redraw(t_interface *itf)
{

	redraw_line(itf);
	move_cursor(itf);


	window.displayed_line = vectors;


    if ()



}

inline void     set_redraw_flags(t_interface *itf, uint64_t *rd_flag)
{
	itf->window.rd_flag = rd_flag;
}

inline void     set_redraw_bounds(t_interface *itf, uint64_t start, uint64_t end)
{
	itf->window.point1 = start;
	itf->window.point2 = end;
}

inline void     set_cursor_pos(t_interface *itf, uint64_t index)
{
	itf->window.point_cursor = index;
}