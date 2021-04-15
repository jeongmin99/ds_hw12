import pymysql #따로 설치해주어야한다.

connect = pymysql.connect(host='localhost', user='hi', password='asd123', db='new_schema',charset='utf8mb4')
cur = connect.cursor()



#위도, 경도 구해서 출력해보기
query = "SELECT 위도,경도 FROM new_schema.asda "
cur.execute(query)
connect.commit()


datas = cur.fetchall()#커서의 모든 데이터를 가져옴
for data in datas:
	print(data)
    
    
#주소만 출력해보기
query="SELECT 소재지도로명주소 FROM new_schema.asda"
cur.execute(query)
connect.commit()


datas = cur.fetchall()
for data in datas:
	print(data)