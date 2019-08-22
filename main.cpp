#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/lambda-runtime/runtime.h>

static aws::lambda_runtime::invocation_response my_handler(aws::lambda_runtime::invocation_request const& req)
{
    /* 解释收到的数据,以JSON格式传进来的哦,如果不正常访问,自然直接让他返回了. */
    Aws::Utils::Json::JsonValue request(req.payload);
    if (!request.WasParseSuccessful()) {
        return aws::lambda_runtime::invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    /* 下面都是构造JSON回应包 */
    Aws::Utils::Json::JsonValue response;
    Aws::Utils::Json::JsonValue headers;
    Aws::Utils::Json::JsonValue parameters(request.View().GetObject("queryStringParameters").WriteCompact()); /* 这个是提取出来的参数. */

    headers.WithString("Content-Type", "application/json"); 
    response.WithString("statusCode", "200");
    response.WithString("body", parameters.View().WriteCompact()); /* 特别注意主体内容是字符串的. */
    response.WithObject("headers", headers);
   
    auto const invocation_payload = response.View().WriteCompact();
    
    /* 返回一定是application/json,否则出错. */
    return aws::lambda_runtime::invocation_response::success(invocation_payload,"application/json");
}

int main()
{
    aws::lambda_runtime::run_handler(my_handler);

    return 0;
}