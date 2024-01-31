package entity;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Date;

@Data
@AllArgsConstructor
public class SelectBook {
    private String bookName; //书名
    private String author; //作者
    private String press; //出版社
    private Double priceLower;//价格下限
    private Double priceLimit; //价格上限
    private String pressDateLower;//时间上限
    private String pressDateLimit;//时间下限
}
